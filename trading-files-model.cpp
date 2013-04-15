#include "trading-files-model.h"

#include <QDebug>
#include <QStringList>
#include <QThread>

struct TradingFilesModel::DataSource {
    QThread *thread;
    TradingFileReader *reader;
    uint recordCount;
};

TradingFilesModel::TradingFilesModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

int TradingFilesModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

int TradingFilesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.count();
}

QVariant TradingFilesModel::headerData(
        int section, Qt::Orientation orientation, int role) const
{
    QVariant data;
    if (orientation == Qt::Horizontal&&
            role == Qt::DisplayRole) {

        switch (section) {
        case Name:
            data = "File Name";
            break;
        case RecordCount:
            data = "Records Read";
            break;
        }
    }
    return data;
}

QVariant TradingFilesModel::data(const QModelIndex &index, int role) const
{
    QVariant data;

    if (index.isValid() && role == Qt::DisplayRole) {
        DataSource *source = m_data[index.row()];
        switch (index.column()) {
        case Name:
            data = source->reader->inputName();
            break;
        case RecordCount:
            data = source->recordCount;
            break;
        };
    }

    return data;
}

bool TradingFilesModel::addSource(QString path) {
    TradingFileReader *reader = new TradingFileReader(path);
    if (reader->isValid()) {
        auto source = new DataSource;
        source->thread = new QThread(this);

        reader->moveToThread(source->thread);
        source->reader = reader;

        source->recordCount = 0;
        connect(source->reader,
                &TradingFileReader::newRecordEncountered, [&]() {
            beginResetModel();
            source->recordCount++;
            endResetModel();
        });

        beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
        m_data.append(source);
        endInsertRows();

        return true;
    } else {
        delete reader;
        return false;
    }
}

bool TradingFilesModel::removeRow(int row, const QModelIndex &parent) {
    if (0 > row || row >= rowCount(parent)) {
        return false;
    }

    beginRemoveRows(parent, row, row);
    m_data.removeAt(row);
    endRemoveRows();

    return true;
}

TradingFilesModel::~TradingFilesModel() {
    for (auto p : m_data) {
        delete p->reader;
        delete p;
    }
}
