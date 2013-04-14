#include "trading-files-model.h"

#include <QDebug>
#include <QStringList>

TradingFilesModel::TradingFilesModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

int TradingFilesModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

int TradingFilesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

QVariant TradingFilesModel::data(const QModelIndex &index, int role) const
{
    QVariant data;

    if (role == Qt::DisplayRole) {
        data = "derp";
    }

    return data;
}
