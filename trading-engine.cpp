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
    } else if ((r.askId() == 6666 || r.bidId() == 6666)) {
        emit newTradeCreated(Trade(r));
    }
}
