#include "trading-signal-generator.h"
#include "record.h"

#include <QDebug>

TradingSignalGenerator::TradingSignalGenerator(QObject *parent) :
    QObject(parent)
{
}

void TradingSignalGenerator::processNewRecord(const Record &r) {
    m_records.append(r);
    emit newRecordGenerated(r);
}

void TradingSignalGenerator::dataProcessingRequested() {
    while(!m_records.isEmpty()) {
        auto r = m_records.takeFirst();
        qDebug() << r;
        emit nextRecord(r);
    }
}
