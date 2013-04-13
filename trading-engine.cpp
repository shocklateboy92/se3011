#include "trading-engine.h"

TradingEngine::TradingEngine(QObject *parent) :
    QObject(parent)
{
}

void TradingEngine::processNewRecord(const Record &r) {
    // do nothing for now
}
