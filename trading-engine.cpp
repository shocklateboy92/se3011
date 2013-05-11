#include "trading-engine.h"
#include "record.h"

#include <QDebug>

TradingEngine::TradingEngine(QObject *parent) :
    QObject(parent)
{
}

void TradingEngine::processNewRecord(const Record &r) {
    switch (r.type()) {

    case Record::Type::ENTER:
        switch (r.bidOrAsk()) {
        case Record::BidAsk::Bid:
            enterBid(Bid(r));
            break;
        case Record::BidAsk::Ask:
            enterAsk(Ask(r));
            break;
        default:
            qWarning() << "encountered record with Type ENTER, but is neither a Bid nor Ask";
        }
        break;
    case Record::Type::DELETE:
        switch (r.bidOrAsk()) {
        case Record::BidAsk::Ask:
            removeAsk(r.askId());
            break;
        case Record::BidAsk::Bid:
            removeBid(r.bidId());
            break;
        default:
            qWarning() << "trying to delete a record that is neither a Bid nor Ask";
        }
        break;
    case Record::Type::AMEND:
        switch (r.bidOrAsk()) {
        case Record::BidAsk::Bid:
            modifyBid(r.bidId(), r.price(), r.volume());
            break;
        case Record::BidAsk::Ask:
            modifyBid(r.askId(), r.price(), r.volume());
            break;
        default:
            qWarning() << "trying to amend a record that is neither a Bid nor Ask";
            break;
        }
        break;

    case Record::Type::TRADE:
        createTrade(Trade(r));
        break;

    default:
        break;
    }
    if (r.type() == Record::Type::TRADE) {
        emit newTradeCreated(Trade(r));
    } else if (r.type() == Record::Type::ENTER && (r.askId() == 6666 || r.bidId() == 6666)) {
        qDebug() << "Found one of our trades: " << r;
        Trade t(r);
        t.setType(Record::Type::TRADE);
        t.setPrice(r.price());
        emit newTradeCreated(t);
    }
}
