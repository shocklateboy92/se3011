#include "trading-engine.h"
#include "record.h"

#include <QDebug>

TradingEngine::TradingEngine(QObject *parent) :
    QObject(parent)
{
}

void TradingEngine::processNewRecord(const Record &record) {
    Record r = record;

    if (r.type() == Record::Type::ENTER && (r.askId() == 6666 || r.bidId() == 6666)) {
        qDebug() << "Found one of our trades: " << r;
        Trade t(r);
        t.setType(Record::Type::TRADE);
        t.setPrice(r.price());
        emit newTradeCreated(t);
        return;
    }

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
}

void TradingEngine::enterBid(Bid bid) {
    Q_ASSERT (!m_bidQueue.contains(bid));

    // find a seller for less than we're offering
    for (Ask ask : m_askQueue) {
        if (ask.price() <= bid.price()) {

            // if we have to make a partial trade
            if (ask.volume() != bid.volume()) {

                // seller has more than we want
                if (ask.volume() > bid.volume()) {
                    Ask a = ask.createPartial(ask.volume() - bid.volume());
                    createTrade(a, bid);

                // we want more from another seller
                } else {
                    Bid b = bid.createPartial(bid.volume() - ask.volume());
                    createTrade(ask, b);
                }
            } else {
                createTrade(ask, bid);
            }
        }

        // if we've completely gone through the bid, there's
        // no point in adding it to the orderbook
        if (bid.volume() == 0) {
            return;
        }
    }

    // if we're still here, we weren't able to fully
    // process the bid
    m_bidQueue.insert(std::lower_bound(m_bidQueue.begin(),
                                       m_bidQueue.end(), bid),
                      bid);
}

void TradingEngine::enterAsk(Ask ask) {
    Q_ASSERT (m_askQueue.count(ask) == 0);

    for (Bid bid : m_bidQueue) {
        if (bid.price() >= ask.price()) {

            if (bid.volume() != ask.volume()) {
                if (bid.volume() > ask.volume()) {
                    Bid b = bid.createPartial(bid.volume() - ask.volume());
                    createTrade(ask, b);
                } else {
                    Ask a = ask.createPartial(ask.volume() - bid.volume());
                    createTrade(a, bid);
                }
            } else {
                createTrade(ask, bid);
            }
        }
    }
    m_askQueue.append(ask);
}

void TradingEngine::removeBid(const Bid &bid) {
    Q_ASSERT (m_bidQueue.count(bid) == 1);
    m_bidQueue.removeOne(bid);
}

void TradingEngine::removeAsk(const Ask &ask) {
    Q_ASSERT (m_askQueue.count(ask) == 1);
    m_askQueue.removeOne(ask);
}

template <typename BidOrAsk>
void modifyOrder(QLinkedList<BidOrAsk> queue, BidOrAsk bidOrAsk) {
    auto r = std::find(queue.begin(), queue.end(), bidOrAsk);
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

//            queue.insert(original);
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

//void TradingEngine::performMatching() {
//    for (Ask a : m_askQueue) {
//        for (Bid b : m_bidQueue) {
//            // if buyer is willing to pay more than
//            // seller asked for, make the trade
//            if (b.price() >= a.price()) {
//                if (b.volume() == a.volume()) {
//                    // buyer's buying exactly what seller is selling,
//                    // both orders are done.
//                    m_askQueue.erase(a);
//                    m_bidQueue.erase(b);
//                }
//                // otherwise, a partial trade occurs
//                else if (b.volume() > a.volume()) {
//                    // buyer wants more, but seller is done
//                    b.setVolume(b.volume() - a.volume());
//                    m_askQueue.erase(a);
//                }
//                else {
//                    // seller has more, buyer is done
//                    a.setVolume(a.volume() - b.volume());
//                    m_bidQueue.erase(b);
//                }

//                createTrade(a, b);
//            }
//        }
//    }
//}

void TradingEngine::createTrade(const Ask &ask, const Bid &bid) {
    auto trade = Trade(ask, bid);
    qDebug() << "Created New Trade: " << trade;
    emit newTradeCreated(trade);
}

void TradingEngine::createTrade(const Trade &existing) {
    emit newTradeCreated(existing);
}
