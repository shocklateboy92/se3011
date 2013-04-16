#include "trades-model.h"

#include <QDebug>
#include <map>

enum ColumnNames {

};

TradesModel::TradesModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

void TradesModel::addRecord(const Record &r)
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


int TradesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.count();
}

int TradesModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    //TODO: update this when I print ALL the info
    return 7;
}

QVariant TradesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant data;
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        data = "Data";
    }
    return data;
}

QVariant TradesModel::data(const QModelIndex &index, int role) const
{
    return "lol";
}
