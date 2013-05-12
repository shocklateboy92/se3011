#ifndef TRADINGENGINE_H
#define TRADINGENGINE_H

#include "record.h"
#include "order.h"

#include <QObject>
#include <QSet>
#include <set>

class TradingEngine : public QObject
{
    Q_OBJECT
public:
    explicit TradingEngine(QObject *parent = 0);

signals:
    void newTradeCreated(const Trade &r);

public slots:
    void processNewRecord(const Record &r);

    void enterBid(const Bid &bid);
    void enterAsk(const Ask &ask);

    void removeBid(const Bid &bid);
    void removeAsk(const Ask &ask);

    void modifyBid(Bid bid);
    void modifyAsk(Ask ask);

    void createTrade(const Ask &ask, const Bid &bid);
    void createTrade(const Trade &existing);

    void performMatching();

private:
    std::set<Ask> m_askQueue;
    std::set<Bid> m_bidQueue;
};

#endif // TRADINGENGINE_H
