#include "records-model.h"

#include <QDebug>
#include <map>

enum ColumnNames {

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
    //TODO: update this when I print ALL the info
    return 7;
}

QVariant RecordsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant data;
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        data = "Data";
    }
    return data;
}

QVariant RecordsModel::data(const QModelIndex &index, int role) const
{
    return "lol";
}
