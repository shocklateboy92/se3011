#ifndef TRADINGENGINE_H
#define TRADINGENGINE_H

#include <QObject>

#include "record.h"

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

    void removeBid(long bidId);
    void removeAsk(long askId);

    void modifyBid(long bidId, double newPrice, double newVolume);
    void modifyAsk(long askId, double newPrice, double newVolume);

    void createTrade(const Ask &ask, const Bid &bid);
    void createTrade(const Trade &existing);
};

#endif // TRADINGENGINE_H
