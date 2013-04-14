#ifndef TRADINGFILESMODEL_H
#define TRADINGFILESMODEL_H

#include <QAbstractTableModel>

class TradingFilesModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TradingFilesModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;
signals:

public slots:

};

#endif // TRADINGFILESMODEL_H
