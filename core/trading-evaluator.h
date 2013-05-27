#ifndef TRADINGEVALUATOR_H
#define TRADINGEVALUATOR_H

#include "order.h"

class GROUP8_CORE TradingEvaluator : public QObject
{
    Q_OBJECT
public:
    explicit TradingEvaluator(QObject *parent = 0);
    struct eval{
        QDateTime datetime;
        float moneySpent;
        float moneyGained;
        float stocksSold;
        float stocksPurchased;
    };

signals:
    void signalTradeEncountered(const Trade &r);
    void currentEval(QDateTime datetime, float moneySpent, float moneyGained, float stocksSold, float stocksPurchased);

public slots:
    void processNewTrade(const Trade &trade);

private:
    int tradeCount;
    float moneySpent;
    float moneyGained;
    float stocksSold;
    float stocksPurchased;
    QList<eval> evals;


};

#endif // TRADINGEVALUATOR_H
