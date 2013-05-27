#include "trading-evaluator.h"
#include "record.h"
#include "order.h"
#include <QDebug>
#include <QString>

TradingEvaluator::TradingEvaluator(QObject *parent) :
    QObject(parent), tradeCount(0)
{
    moneySpent = 0;
    moneyGained = 0;
    stocksPurchased = 0;
    stocksSold = 0;

}

void TradingEvaluator::processNewTrade(const Trade &trade) {
    // also do nothing
//    qDebug() << QStringLiteral("evaluating trade #%1...").arg(tradeCount++);
//    qDebug() <<*((Record*)&trade);

    if (trade.askId() == 6666) {
        emit signalTradeEncountered(trade);

        moneySpent += trade.value();
        stocksPurchased += trade.volume();

    } else if (trade.bidId() == 6666) {
        emit signalTradeEncountered(trade);

        moneyGained += trade.value();
        stocksSold += trade.volume();

    }

    //qDebug() << "MoneySpent:" << moneySpent;
    struct eval a ={
        QDateTime(trade.date(), trade.time()),
        moneySpent,
        moneyGained,
        stocksSold,
        stocksPurchased
    };

    evals.append(a);
    //qDebug() << "eval: " << evals.size();

    if(evals.size() == 200) {
        emit currentEval(evals);
        evals.clear();
    }

}

int der = qRegisterMetaType<QList<TradingEvaluator::eval>>("QList<eval>");
