#ifndef TRADINGFILESMODEL_H
#define TRADINGFILESMODEL_H

#include "trading-file-reader.h"

#include <QAbstractTableModel>

class TradingFilesModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TradingFilesModel(QObject *parent = 0);
    virtual ~TradingFilesModel();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
signals:

public slots:
    bool addSource(QString path);
    bool removeRow(int row, const QModelIndex &parent = QModelIndex());

private:
    class DataSource;
    QList<DataSource*> m_data;

    enum ColumnNames {
        Name = 0,
        RecordCount
    };
};

#endif // TRADINGFILESMODEL_H
