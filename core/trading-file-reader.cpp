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
    m_stream.setDevice(file);
    m_valid = true;
}


void TradingFileReader::startReading()
{
    qDebug() << "GAH!";

    // in case we've read the file before
    m_stream.seek(0);
    //ignore header line
    m_stream.readLine();

    while (!m_stream.atEnd()) {
        Record r;
        m_stream >> r;
        if (r.isValid()) {
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
