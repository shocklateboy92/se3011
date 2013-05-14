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
    return 1;
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
//        case RecordCount:
//            data = "Records Read";
//            break;
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
//        case RecordCount:
//            data = source->recordCount;
//            break;
        };
    }

    return data;
}

bool TradingFilesModel::addSource(QString path) {
    TradingFileReader *reader = new TradingFileReader(path);
    if (reader->isValid()) {
        auto source = new DataSource;
        source->thread = new QThread();
        source->thread->start();

        reader->moveToThread(source->thread);
        source->reader = reader;

        connect(this, &TradingFilesModel::dataProcessingRequested,
                source->reader, &TradingFileReader::startReading);
        connect(source->reader, &TradingFileReader::newRecordEncountered,
                this, &TradingFilesModel::newRecordEncountered);

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
    DataSource *source = m_data.takeAt(row);
    delete source->reader;
    delete source;
    endRemoveRows();

    return true;
}

TradingFilesModel::~TradingFilesModel() {
    for (DataSource *p : m_data) {
        p->thread->quit();
        p->thread->wait();
        delete p->thread;
        delete p->reader;
        delete p;
    }
}
