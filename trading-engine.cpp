#include "trading-engine.h"
#include "record.h"

#include <QDebug>

TradingEngine::TradingEngine(QObject *parent) :
    QObject(parent)
{
}

void TradingEngine::processNewRecord(const Record &r) {
    if (r.type() == Record::Type::TRADE) {
        emit newTradeCreated(Trade(r));
    }
}
