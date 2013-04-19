#include "trading-signal-generator.h"
#include "record.h"

#include <QDebug>

TradingSignalGenerator::TradingSignalGenerator(QObject *parent) :
    QObject(parent)
{
}

void TradingSignalGenerator::processNewRecord(const Record &r) {
    m_records.push_back(&r);
    emit newRecordGenerated(r);
}

void TradingSignalGenerator::dataProcessingRequested() {
    while(!m_records.isEmpty()) {
        const Record *r = m_records.takeFirst();
        qDebug() << r;
        emit nextRecord(*r);
    }
}
