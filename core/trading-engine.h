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
    void processNewRecord(Record::Ptr r);

    void enterBid(Bid bid);
    void enterAsk(Ask ask);

    void removeBid(Bid bid);
    void removeAsk(Ask ask);

    void modifyBid(Bid bid);
    void modifyAsk(Ask ask);

    void createTrade(Ask ask, Bid bid);
    void createTrade(const Trade &existing);

//    void performMatching();

private:
    QMap<QByteArray, QLinkedList<Ask>> m_askQueues;
    QMap<QByteArray, QLinkedList<Bid>> m_bidQueues;

    friend class TradingEngineTests;
};

#endif // TRADINGENGINE_H
