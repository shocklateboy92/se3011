#include "records-model.h"

#include <QDebug>
#include <QList>

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

        switch (static_cast<ColumnName>(index.column())) {
        case ColumnName::Instrument:
            data = r.instrument();
            break;
        case ColumnName::Date:
            data = r.date();
            break;
        case ColumnName::Time:
            data = r.time();
            break;
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
        case ColumnName::Price:
            data = r.price();
            break;
        case ColumnName::Volume:
            data = r.volume();
            break;
        case ColumnName::Value:
            data = r.value();
            break;
        case ColumnName::TransID:
            data = qlonglong(r.transactionId());
            break;
        case ColumnName::BidID:
            data = qlonglong(r.bidId());
            break;
        case ColumnName::AskID:
            data = qlonglong(r.askId());
            break;
        default:
            break;
        }
    }

    return data;
}
