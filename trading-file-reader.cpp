#include "trading-file-reader.h"
#include <QDebug>

TradingFileReader::TradingFileReader(QObject *parent) :
    QObject(parent)
{
}


void TradingFileReader::startReading(QTextStream &is)
{
    qDebug();
    while (!is.atEnd()) {
        Record r;
        is >> r;
        if (r.isValid()) {
            emit newRecordEncountered(r);
        }
    }
}
