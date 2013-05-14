#ifndef TRADINGENGINE_H
#define TRADINGENGINE_H

#include "record.h"
#include "order.h"

#include <QObject>
#include <QLinkedList>

class GROUP8_CORE TradingEngine : public QObject
{
    Q_OBJECT
public:
    explicit TradingEngine(QObject *parent = 0);

signals:
    void newTradeCreated(const Trade &r);

public slots:
    void processNewRecord(const Record &r);

    void enterBid(Bid bid);
    void enterAsk(Ask ask);

    void removeBid(const Bid &bid);
    void removeAsk(const Ask &ask);

    void modifyBid(Bid bid);
    void modifyAsk(Ask ask);

    void createTrade(const Ask &ask, const Bid &bid);
    void createTrade(const Trade &existing);

//    void performMatching();

private:
    QLinkedList<Ask> m_askQueue;
    QLinkedList<Bid> m_bidQueue;

    friend class TradingEngineTests;
};

#endif // TRADINGENGINE_H
