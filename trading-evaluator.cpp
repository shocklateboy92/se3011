#include "trading-evaluator.h"
#include "record.h"
#include <QDebug>
#include <QString>

TradingEvaluator::TradingEvaluator(QObject *parent) :
    QObject(parent), tradeCount(0)
{
    moneySpent = 0;
    moneyGained = 0;

}

void TradingEvaluator::processNewTrade(const Trade &trade) {
    // also do nothing
    qDebug() << QStringLiteral("evaluating trade #%1...").arg(tradeCount++);
    qDebug() <<*((Record*)&trade);

    if (trade.askId() == 6666) {
        moneySpent += trade.value();
        emit signalTradeEncountered(trade);

    } else if (trade.bidId() == 6666) {

        moneyGained += trade.value();
        emit signalTradeEncountered(trade);
    }

    emit currentEval(moneySpent, moneyGained);
}
