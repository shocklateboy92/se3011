#include "trading-file-reader.h"
#include <QDebug>
#include <QFile>

TradingFileReader::TradingFileReader(const QString &fileName, QObject *parent) :
    QObject(parent), m_fileName(fileName)
{
    QFile *file = new QFile(fileName, this);
    if (!file->open(QIODevice::ReadOnly)) {
        qWarning() << "failed to open" << fileName << ":" << file->errorString();
        return;
    }
    m_stream = file;
    m_valid = true;
}


void TradingFileReader::startReading()
{
    qDebug() << "GAH!";
    if (!m_valid) {
        return;
    }

    // in case we've read the file before
    m_stream->seek(0);
    //ignore header line
    m_stream->readLine();

    while (!m_stream->atEnd()) {
        QByteArray csvLine = m_stream->readLine();
        Record::Ptr r = Record::fromCSV(csvLine);
        if (r) {
            emit newRecordEncountered(r);
        }
    }
}

bool TradingFileReader::isValid() const {
    return m_valid;
}

QString TradingFileReader::inputName() const {
    return m_fileName;
}
