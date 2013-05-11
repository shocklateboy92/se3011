#include "records-model.h"

#include <QVariant>
#include <QDebug>
#include <QList>

#include <functional>
#include <unordered_map>

enum class ColumnName {
    Instrument,
    Date,
    Time,
    RecordType,
    Price,
    Volume,
    UndisclosedVolume,
    Value,
    Qualifiers,
    TransID,
    BidID,
    AskID,
    BidAsk,
    EntryTime,
    OldPrice,
    OldVolume,
    BuyerBrokerID,
    SellerBrokerID
};

struct cHash {
    std::size_t operator()(ColumnName n) const {
        return std::hash<int>()(static_cast<int>(n));
    }
};

template <typename Return, typename Object>
QVariant mVar5(std::function<Return(const Object&)> f, Object *o) {
    return QVariant(f(*o));
}

template <typename T>
std::function<QVariant(Record *r)>
O_(std::function<T(const Record&)> f) {
    return std::bind(&mVar5<T, Record>, f, std::placeholders::_1);
}

static const std::unordered_map<ColumnName,
std::function<QVariant(Record*)>, cHash> column_getters  {
    {ColumnName::Instrument, O_<QString>(&Record::instrument)},
    {ColumnName::Date, O_<QDate>(&Record::date)},
    {ColumnName::Time, O_<QTime>(&Record::time)},

    {ColumnName::Price, O_<double>(&Record::price)},
    {ColumnName::Volume, O_<double>(&Record::volume)},
    {ColumnName::Value, O_<double>(&Record::value)},
    {ColumnName::TransID, O_<qint64>(&Record::transactionId)},
    {ColumnName::BidID, O_<qint64>(&Record::bidId)},
    {ColumnName::AskID, O_<qint64>(&Record::askId)}
};

static const QList<QString> column_strings = {
    "Instrument",
    "Date",
    "Time",
    "Record Type",
    "Price",
    "Volume",
    "Undisclosed Volume",
    "Value",
    "Qualifiers",
    "Trans ID",
    "Bid ID",
    "Ask ID",
    "Bid/Ask",
    "Entry Time",
    "Old Price",
    "Old Volume",
    "Buyer Broker ID",
    "Seller Broker ID"
};



RecordsModel::RecordsModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

void RecordsModel::addRecord(const Record &r)
{
    if (!r.isValid()) {
        qWarning() << "Attempting to store invalid record " << r;
        // fuck it - store it anyway
//        return;
    }

    beginInsertRows(QModelIndex(), m_data.count(), m_data.count());
    m_data.append(r);
    endInsertRows();
}


int RecordsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.count();
}

int RecordsModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return column_strings.length();
}

QVariant RecordsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant data;
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        return column_strings[section];
    }
    return data;
}

QVariant RecordsModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(index);
    QVariant data;

    if (role == Qt::DisplayRole && index.isValid()) {
        Record r = m_data.at(index.row());

        ColumnName col = static_cast<ColumnName>(index.column());
        if (column_getters.count(col) > 0) {
            data = column_getters.at(col)(&r);
        } else {
            switch (static_cast<ColumnName>(index.column())) {

            case ColumnName::RecordType:
                if (r.type() == Record::Type::AMEND) {
                    data = "Amend";
                } else if (r.type() == Record::Type::ENTER) {
                    data = "Enter";
                } else if (r.type() == Record::Type::DELETE) {
                    data = "Delete";
                } else if (r.type() == Record::Type::TRADE) {
                    data = "Trade";
                } else {
                    data = "UNKNOWN";
                }
                break;
            default:
                break;
            }
        }
    }

    return data;
}

bool RecordsModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    qDebug() << row << ',' << count;

    if (row + count > m_data.size()) {
        return false;
    }

    beginRemoveRows(QModelIndex(), row, row + count -1);
    while (count) {
        m_data.removeAt(row);
        count--;
    }
    endRemoveRows();

    return true;
}
