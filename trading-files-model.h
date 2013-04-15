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
signals:

public slots:
    bool addSource(QString path);

private:
    class DataSource;
    QList<DataSource*> m_data;

    enum ColumnNames {
        Name = 0,
        RecordCount
    };
};

#endif // TRADINGFILESMODEL_H