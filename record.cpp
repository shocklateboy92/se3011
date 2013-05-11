#include "record.h"

#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QDataStream>
#include <QRegularExpression>
#include <QDebug>
#include <unordered_map>

// because QMap doesn't support initializer lists yet
static std::unordered_map<std::string, Record::Type> type_strings = {
    {"ENTER", Record::Type::ENTER},
    {"AMEND", Record::Type::AMEND},
    {"TRADE", Record::Type::TRADE},
    {"DELETE", Record::Type::DELETE}
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
    if (!type_strings.count(line[3].toStdString())) {
        r.m_valid = false;
        return in;
    }
    r.setType(type_strings.operator [](it.next().toStdString()));
    r.setPrice(it.next().toDouble(&ok));
    if (!ok) {
        r.setPrice(0);
        //qWarning() << "failed to parse: " << line;
    }
    //it.next(); // not sure what this is
    r.setVolume(it.next().toDouble());
    r.setValue(it.next().toDouble());
    //more stuff
    //TODO: Parse the rest of the line

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
    return m_value;
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

int rd = qRegisterMetaType<Record>("Record");
