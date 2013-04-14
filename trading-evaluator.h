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

public slots:
    void processNewTrade(const Trade &trade);

private:
    int tradeCount;
};

#endif // TRADINGEVALUATOR_H
