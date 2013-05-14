#include "record.h"

#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QDataStream>
#include <QRegularExpression>
#include <QDebug>
#include <unordered_map>

// Hashing functions - have to be at the top for everything else to work
namespace std {
template <>
struct hash<QString> {
    std::size_t operator ()(const QString &str) const {
        return qHash(str);
    }
};
template <>
struct hash<Record::Type> {
    std::size_t operator ()(Record::Type t) const {
        return hash<int>()(static_cast<int>(t));
    }
};
template <>
struct hash<Record::Field> {
    std::size_t operator()(Record::Field n) const {
        return std::hash<int>()(static_cast<int>(n));
    }
};
}
template <typename T>
constexpr std::function<QVariant(const Record *r)>
O_(std::function<T(const Record&)> f) {
    return [=](const Record* r)-> QVariant {return f(*r);};
}

static const std::unordered_map<QString, Record::Type> type_strings = {
    {"ENTER", Record::Type::ENTER},
    {"AMEND", Record::Type::AMEND},
    {"TRADE", Record::Type::TRADE},
    {"DELETE", Record::Type::DELETE}
};

static const std::unordered_map<Record::Type, QString> type_strings_reverse = {
    {Record::Type::ENTER, "ENTER"},
    {Record::Type::AMEND, "AMEND"},
    {Record::Type::TRADE, "TRADE"},
    {Record::Type::DELETE, "DELETE"}
};

static const std::unordered_map<Record::Field, QString> field_names= {
    {Record::Field::Instrument,         "Instrument"},
    {Record::Field::Date,               "Date"},
    {Record::Field::Time,               "Time"},
    {Record::Field::RecordType,         "Record Type"},
    {Record::Field::Price,              "Price"},
    {Record::Field::Volume,             "Volume"},
    {Record::Field::UndisclosedVolume,  "Undisclosed Volume"},
    {Record::Field::Value,              "Value"},
    {Record::Field::Qualifiers,         "Qualifiers"},
    {Record::Field::TransID,            "Trans ID"},
    {Record::Field::BidID,              "Bid ID"},
    {Record::Field::AskID,              "Ask ID"},
    {Record::Field::BidAsk,             "Bid/Ask"},
    {Record::Field::EntryTime,          "Entry Time"},
    {Record::Field::OldPrice,           "Old Price"},
    {Record::Field::OldVolume,          "Old Volume"},
    {Record::Field::BuyerBrokerID,      "Buyer Broker ID"},
    {Record::Field::SellerBrokerID,     "Seller Broker ID"}
};

static const std::unordered_map<Record::Field,
std::function<QVariant(const Record*)>> field_getters  {
    {Record::Field::Instrument, O_<QString>(&Record::instrument)},
    {Record::Field::Date,       O_<QDate>(&Record::date)},
    {Record::Field::Time,       O_<QTime>(&Record::time)},
    {Record::Field::RecordType, O_<QString>(&Record::typeName)},
    {Record::Field::Price,      O_<double>(&Record::price)},
    {Record::Field::Volume,     O_<double>(&Record::volume)},
    {Record::Field::Value,      O_<double>(&Record::value)},
    {Record::Field::TransID,    O_<qint64>(&Record::transactionId)},
    {Record::Field::BidID,      O_<qint64>(&Record::bidId)},
    {Record::Field::AskID,      O_<qint64>(&Record::askId)}
};

Record::Record() :
    m_valid(true)
{
}

bool Record::isValid() const {
    //FIXME: run some sanity checks here
    return m_valid;
}


QTextStream& operator >>(QTextStream &in, Record &r) {
    static QRegularExpression sep(",");
    QStringList line = in.readLine().split(sep);

    if (line.first().startsWith('#')) {
        r.m_valid = false;
        qDebug() << "invalid record line:" << line;
        return in;
    }

    QStringListIterator it(line);

    bool ok = false;

    r.setInstrument(it.next());
    r.setDate(QDate::fromString(it.next(), "yyyyMMdd"));
    r.setTime(QTime::fromString(it.next(), "hh:mm:ss.zzz"));
    if (!type_strings.count(line[3])) {
        r.m_valid = false;
        return in;
    }
    r.setType(type_strings.at(it.next()));
    r.setPrice(it.next().toDouble(&ok));
    if (!ok) {
        r.setPrice(0);
        //qWarning() << "failed to parse: " << line;
    }

    r.setVolume(it.next().toDouble());
    it.next(); // don't care about undisclosedVolume
    r.setValue(it.next().toDouble());
    it.next(); // don't care about qualifiers

    r.setTransId(it.next().toLong());
    r.setBidId(it.next().toLong());
    r.setAskId(it.next().toLong());
    QString bidOrAskStr = it.next();
    if (bidOrAskStr == "A") {
        r.setBidOrAsk(Record::BidAsk::Ask);
    } else if (bidOrAskStr == "B") {
        r.setBidOrAsk(Record::BidAsk::Bid);
    } else {
        r.setBidOrAsk(Record::BidAsk::Neither);
    }

    //FIXME - sooo not true!
    r.m_valid = true;

    return in;
}

QDebug operator << (QDebug os, const Record &r) {
    os << r.instrument();
    os << r.price();
    os << r.volume();
    os << r.value();
    os << r.date();
    os << r.time();
    os << r.bidId();
    os << r.askId();
    return os;
}


QString Record::instrument() const
{
    return m_instrument;
}

void Record::setInstrument(const QString &value)
{
    m_instrument = value;
}

QDate Record::date() const
{
    return m_date;
}

void Record::setDate(const QDate &value)
{
    m_date = value;
}

QTime Record::time() const
{
    return m_time;
}

void Record::setTime(const QTime &value)
{
    m_time = value;
}

Record::Type Record::type() const
{
    return m_type;
}

void Record::setType(const Type &value)
{
    m_type = value;
}

double Record::volume() const
{
    return m_volume;
}

void Record::setVolume(double value)
{
    m_volume = value;
}

double Record::price() const
{
    return m_price;
}

void Record::setPrice(double value)
{
    m_price = value;
}

double Record::value() const
{
    return m_price * m_volume;
}

void Record::setValue(double value)
{
    m_value = value;
}

long Record::transactionId() const
{
    return m_transId;
}

void Record::setTransId(long value)
{
    m_transId = value;
}

long Record::bidId() const
{
    return m_bidId;
}

void Record::setBidId(long value)
{
    m_bidId = value;
}

long Record::askId() const
{
    return m_askId;
}

void Record::setAskId(long value)
{
    m_askId = value;
}

Record::BidAsk Record::bidOrAsk() const
{
    return m_bidOrAsk;
}

void Record::setBidOrAsk(const BidAsk &value)
{
    m_bidOrAsk = value;
}

long Record::buyerId() const
{
    return m_buyerId;
}

void Record::setBuyerId(long id)
{
    m_buyerId = id;
}

long Record::sellerId() const
{
    return m_sellerId;
}

void Record::setSellerId(long id)
{
    m_sellerId = id;
}

int rd = qRegisterMetaType<Record>("Record");


QVariant Record::fieldValue(Record::Field field) const
{
    if (field_getters.count(field) > 0) {
        return field_getters.at(field)(this);
    } else {
        return QVariant();
    }
}

QString Record::typeName() const
{
    if (type_strings_reverse.count(type()) > 0) {
        return type_strings_reverse.at(type());
    } else {
        return QStringLiteral("UNKOWN");
    }
}

std::size_t Record::numFields()
{
    // hack, since fields are numbered sequentially
    return static_cast<int>(Field::NotAField);
}

QString Record::fieldName(Field field)
{
    Q_ASSERT (field_names.count(field) > 0);
    return field_names.at(field);
}
