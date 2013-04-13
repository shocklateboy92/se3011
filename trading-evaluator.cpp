#include "trading-evaluator.h"

TradingEvaluator::TradingEvaluator(QObject *parent) :
    QObject(parent)
{
}

void TradingEvaluator::processNewTrade(const Trade &trade) {
    // also do nothing
}
