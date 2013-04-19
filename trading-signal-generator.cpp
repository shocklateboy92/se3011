#include "trading-signal-generator.h"
#include "record.h"

#include <QDebug>

TradingSignalGenerator::TradingSignalGenerator(QObject *parent) :
    QObject(parent)
{
}

void TradingSignalGenerator::processNewRecord(const Record &r) {
    emit newRecordGenerated(r);
}
