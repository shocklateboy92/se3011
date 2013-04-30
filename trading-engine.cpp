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
    } else if (r.type() == Record::Type::ENTER && (r.askId() == 6666 || r.bidId() == 6666)) {
        qDebug() << "Found one of our trades: " << r;
        Trade t(r);
        t.setType(Record::Type::TRADE);
        emit newTradeCreated(t);
    }
}
