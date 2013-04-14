#include "trading-evaluator.h"
#include <QDebug>
#include <QString>

TradingEvaluator::TradingEvaluator(QObject *parent) :
    QObject(parent), tradeCount(0)
{
}

void TradingEvaluator::processNewTrade(const Trade &trade) {
    // also do nothing
    qDebug() << QStringLiteral("evaluating trade #%1...").arg(tradeCount++);
}
