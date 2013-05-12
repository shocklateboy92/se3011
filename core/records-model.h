#ifndef TRADESMODEL_H
#define TRADESMODEL_H

#include "record.h"

#include <QAbstractTableModel>

class RecordsModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit RecordsModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    
signals:
    
public slots:
    void addRecord(const Record &r);
    bool removeRows(int row, int count, const QModelIndex &parent);
    
private:
    QList<Record> m_data;
};

#endif // TRADESMODEL_H
