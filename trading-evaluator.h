#ifndef TRADINGEVALUATOR_H
#define TRADINGEVALUATOR_H

#include <QObject>

class Trade;

class TradingEvaluator : public QObject
{
    Q_OBJECT
public:
    explicit TradingEvaluator(QObject *parent = 0);

signals:
    void signalTradeEncountered(const Trade &r);
    void currentEval(float moneySpent, float moneyGained);

public slots:
    void processNewTrade(const Trade &trade);

private:
    int tradeCount;
    float moneySpent;
    float moneyGained;
};

#endif // TRADINGEVALUATOR_H
