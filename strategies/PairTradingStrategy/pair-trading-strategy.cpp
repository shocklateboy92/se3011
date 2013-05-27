#include "pair-trading-strategy.h"
#include "pair-trading-widget.h"

QDockWidget *PairTradingStrategy::configWidget()
{
    auto widget = new PairTradingWidget();
    connect(widget, &PairTradingWidget::newPair,
            this, &PairTradingStrategy::processPair);
    connect(widget, &PairTradingWidget::deletePair,
            this, &PairTradingStrategy::removePair);

    return widget;
}

void PairTradingStrategy::processTrade(const Trade &trade)
{
}

PairTradingStrategy::PairTradingStrategy(QObject *parent)
    : QObject (parent)
{
    
    
    
    
}


void PairTradingStrategy::processPair(const PairTradingStrategy::PairData pd)
{
    //m_pairs.append(pd);
}

void PairTradingStrategy::removePair(const PairTradingStrategy::PairData pd)
{
    //m_pairs.removeOne(pd);
}


void PairTradingStrategy::reset()
{
}
