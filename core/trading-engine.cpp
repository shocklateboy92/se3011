#include "trading-engine.h"
#include "record.h"

#include <QDebug>

TradingEngine::TradingEngine(QObject *parent) :
    QObject(parent)
{
}

void TradingEngine::processNewRecord(Record::Ptr r) {

    if (r->type() == Record::Type::ENTER && (r->askId() == 6666 || r->bidId() == 6666)) {
        qDebug() << "Found one of our trades: " << r;
        Trade t(*r);
        t.setType(Record::Type::TRADE);
        t.setPrice(r->price());
        emit newTradeCreated(t);
        return;
    }

    switch (r->type()) {

    case Record::Type::ENTER:
        switch (r->bidOrAsk()) {
        case Record::BidAsk::Bid:
            enterBid(Bid(r));
            break;
        case Record::BidAsk::Ask:
            enterAsk(Ask(r));
            break;
        default:
            qWarning() << "encountered record with Type ENTER, but is neither a Bid nor Ask";
            break;
        }
        break;
    case Record::Type::DELETE:
        switch (r->bidOrAsk()) {
        case Record::BidAsk::Ask:
            removeAsk(Ask(r));
            break;
        case Record::BidAsk::Bid:
            removeBid(Bid(r));
            break;
        default:
            qWarning() << "trying to delete a record that is neither a Bid nor Ask";
            break;
        }
        break;
    case Record::Type::AMEND:
        switch (r->bidOrAsk()) {
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
//        createTrade(Trade(*r.data()));
        break;

    default:
        break;
    }
}

void TradingEngine::enterBid(Bid bid) {
    auto &m_bidQueue = m_bidQueues[bid.instrument()];
    auto &m_askQueue = m_askQueues[bid.instrument()];

    if (m_bidQueue.contains(bid)) {
        qDebug() << "skipping duplicate bid with id : " << bid.id();
        return;
    }

    // find a seller for less than we're offering
    for (auto it = m_askQueue.begin(); it != m_askQueue.end(); ) {
        Ask ask = *it;
        if (ask.price() <= bid.price()) {

            // if we have to make a partial trade
            if (ask.volume() != bid.volume()) {

                // seller has more than we want
                // leaves sell in queue with smaller volume
                if (ask.volume() > bid.volume()) {
                    Ask a = ask.createPartial(bid.volume());
                    createTrade(a, bid);
                    ++it;

                // we want more from another seller
                // removes sell, as it's completed
                } else {
                    Bid b = bid.createPartial(ask.volume());
                    it = m_askQueue.erase(it);
                    createTrade(ask, b);
                }
            } else {
                it = m_askQueue.erase(it);
                createTrade(ask, bid);
            }
        } else {
            ++it;
        }

        // if we've completely gone through the bid, there's
        // no point in adding it to the orderbook
        if (bid.volume() == 0) {
            return;
        }
    }

    // if we're still here, we weren't able to fully
    // process the bid
    auto pos = std::lower_bound(m_bidQueue.begin(), m_bidQueue.end(), bid);
    m_bidQueue.insert(pos, bid);
}

void TradingEngine::enterAsk(Ask ask) {
    auto &m_bidQueue = m_bidQueues[ask.instrument()];
    auto &m_askQueue = m_askQueues[ask.instrument()];

    if (m_askQueue.contains(ask)) {
        qDebug() << "skipping duplicate ask with id : " << ask.id();
        return;
    }

    auto it = m_bidQueue.begin();
    while (it != m_bidQueue.end()) {
        Bid bid = *it;

        if (bid.price() >= ask.price()) {

            if (bid.volume() != ask.volume()) {
                if (bid.volume() > ask.volume()) {
                    Bid b = bid.createPartial(ask.volume());
                    ++it;
                    createTrade(ask, b);
                } else {
                    Ask a = ask.createPartial(bid.volume());
                    it = m_bidQueue.erase(it);
                    createTrade(a, bid);
                }
            } else {
                it = m_bidQueue.erase(it);
                createTrade(ask, bid);
            }

            if (ask.volume() == 0) {
                // already been fully processed
                return;
            }
        } else {
            ++it;
        }
    }

    m_askQueue.insert(std::lower_bound(
                          m_askQueue.begin(),
                          m_askQueue.end(),
                          ask),
                      ask);
}

void TradingEngine::removeBid(Bid bid) {
    m_bidQueues[bid.instrument()].removeOne(bid);
}

void TradingEngine::removeAsk(Ask ask) {
    m_askQueues[ask.instrument()].removeOne(ask);
}

template <typename BidOrAsk>
void modifyOrder(QLinkedList<BidOrAsk> &queue, BidOrAsk &bidOrAsk) {
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

            queue.insert(std::lower_bound(queue.begin(),
                                          queue.end(),
                                          bidOrAsk),
                          bidOrAsk);
        } else {
            // if only the volume has decreased, it
            // doesn't loose its position.
            original.setVolume(bidOrAsk.volume());
        }
    }
}

void TradingEngine::modifyBid(Bid bid) {
    modifyOrder(m_bidQueues[bid.instrument()], bid);
}

void TradingEngine::modifyAsk(Ask ask) {
    modifyOrder(m_askQueues[ask.instrument()], ask);
}

void TradingEngine::createTrade(Ask ask, Bid bid) {
    auto trade = Trade(ask, bid);
//    qDebug() << "Created New Trade: " << trade;
    emit newTradeCreated(trade);
}

void TradingEngine::createTrade(const Trade &existing) {
    emit newTradeCreated(existing);
}
