#include "records-model.h"

#include <QVariant>
#include <QDebug>
#include <QList>

#include <functional>
#include <unordered_map>


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
    return Record::numFields();
}

QVariant RecordsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant data;
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        return Record::fieldName(static_cast<Record::Field>(section));
    }
    return data;
}

const QList<Record> &RecordsModel::records() const
{
    return m_data;
}

QVariant RecordsModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(index);
    QVariant data;

    if (role == Qt::DisplayRole && index.isValid()) {
        Record r = m_data.at(index.row());

        Record::Field col = static_cast<Record::Field>(index.column());
        data = r.fieldValue(col);
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
