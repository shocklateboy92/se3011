#include "trading-engine.h"
#include "record.h"

#include <QDebug>

TradingEngine::TradingEngine(QObject *parent) :
    QObject(parent)
{
}

void TradingEngine::processNewRecord(const Record &record) {
    Record r = record;

    switch (r.type()) {

    case Record::Type::ENTER:
        if (r.askId() == 6666 || r.bidId() == 6666) {
            qDebug() << "Found one of our trades: " << r;
            Trade t(r);
            t.setType(Record::Type::TRADE);
            t.setPrice(r.price());
            emit newTradeCreated(t);
        }
        break;
    case Record::Type::DELETE:
    case Record::Type::AMEND:
//        qDebug() << "ignoring record of type" << r.typeName();
        break;

    case Record::Type::TRADE:
        createTrade(Trade(r));
        break;

    default:
        break;
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

void TradingEngine::performMatching() {
    for (Ask a : m_askQueue) {
        for (Bid b : m_bidQueue) {
            // if buyer is willing to pay more than
            // seller asked for, make the trade
            if (b.price() >= a.price()) {
                if (b.volume() == a.volume()) {
                    // buyer's buying exactly what seller is selling,
                    // both orders are done.
                    m_askQueue.erase(a);
                    m_bidQueue.erase(b);
                }
                // otherwise, a partial trade occurs
                else if (b.volume() > a.volume()) {
                    // buyer wants more, but seller is done
                    b.setVolume(b.volume() - a.volume());
                    m_askQueue.erase(a);
                }
                else {
                    // seller has more, buyer is done
                    a.setVolume(a.volume() - b.volume());
                    m_bidQueue.erase(b);
                }

                createTrade(a, b);
            }
        }
    }
}

void TradingEngine::createTrade(const Ask &ask, const Bid &bid) {
    auto trade = Trade(ask, bid);
    qDebug() << "Created New Trade: " << trade;
    emit newTradeCreated(trade);
}

void TradingEngine::createTrade(const Trade &existing) {
    emit newTradeCreated(existing);
}
