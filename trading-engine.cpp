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
            removeAsk(Ask(r));
            break;
        case Record::BidAsk::Bid:
            removeBid(Bid(r));
            break;
        default:
            qWarning() << "trying to delete a record that is neither a Bid nor Ask";
        }
        break;
    case Record::Type::AMEND:
        switch (r.bidOrAsk()) {
        case Record::BidAsk::Ask:
            modifyAsk(Ask(r));
            break;
        case Record::BidAsk::Bid:
            modifyBid(Bid(r));
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

void TradingEngine::enterBid(const Bid &bid) {
    Q_ASSERT (m_bidQueue.count(bid) == 0);
    m_bidQueue.insert(bid);
    performMatching();
}

void TradingEngine::enterAsk(const Ask &ask) {
    Q_ASSERT (m_askQueue.count(ask) == 0);
    m_askQueue.insert(ask);
    performMatching();
}

void TradingEngine::removeBid(const Bid &bid) {
    Q_ASSERT (m_bidQueue.count(bid) == 1);
    m_bidQueue.erase(bid);
}

void TradingEngine::removeAsk(const Ask &ask) {
    Q_ASSERT (m_askQueue.count(ask) == 1);
    m_askQueue.erase(ask);
}

template <typename BidOrAsk>
void modifyOrder(std::set<BidOrAsk> queue, BidOrAsk bidOrAsk) {
    auto r = queue.find(bidOrAsk);
    if (r != queue.end()) {
        BidOrAsk original = *r;
        Q_ASSERT (original.id() == bidOrAsk.id());

        if (original.price() != bidOrAsk.price() ||
                original.volume() > bidOrAsk.volume()) {

            // remove and re-add to loose position
            queue.erase(r);

            original.setPrice(bidOrAsk.price());
            original.setVolume(bidOrAsk.volume());

            // since this simulation happens long past,
            // we can't use the current time.
            original.setTime(bidOrAsk.time());
            original.setDate(bidOrAsk.date());

            queue.insert(original);
        } else {
            // if only the volume has decreased, it
            // doesn't loose its position.
            original.setVolume(bidOrAsk.volume());
        }
    }
}

void TradingEngine::modifyBid(Bid bid) {
    modifyOrder(m_bidQueue, bid);
}

void TradingEngine::modifyAsk(Ask ask) {
    modifyOrder(m_askQueue, ask);
}
