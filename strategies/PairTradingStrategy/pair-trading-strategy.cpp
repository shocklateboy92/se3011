#include <QDebug>
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

PairTradingStrategy::PairTradingStrategy(QObject *parent)
    : QObject (parent)
{
    

}


void PairTradingStrategy::processPair(const PairTradingStrategy::PairData pd)
{
    m_pairs.append(pd);
}

void PairTradingStrategy::removePair(const PairTradingStrategy::PairData pd)
{
    m_pairs.removeOne(pd);
}


void PairTradingStrategy::reset()
{
    for (PairTradingStrategy::PairData &ins : m_pairs) {
        ins = PairData(ins.longInstrument, ins.shortInstrument);
    }
}


void PairTradingStrategy::processTrade(const Trade &trade)
{

    for (PairData p : m_pairs) {
        if (trade.instrument() == p.longInstrument) {
            p.previousPriceH = trade.price();

        } else if (trade.instrument() == p.shortInstrument) {
            p.previousPriceL = trade.price();
        }

        double currentSpread = p.previousPriceH - p.previousPriceL;
        p.historySize++;

        double sellPrice = 0.0;
        double buyPrice = 0.0;
        QByteArray sellInstrument;
        QByteArray buyInstrument;

        if (currentSpread >= p.historicalSpread) {
            if(currentSpread <= p.previousSpread ) {
                sellPrice = p.previousPriceH;
                buyPrice = p.previousPriceL;
                sellInstrument = p.longInstrument;
                buyInstrument = p.shortInstrument;
            }
        } else if (currentSpread <= p.historicalSpread) {
            if(currentSpread >= p.previousSpread ) {
                sellPrice = p.previousPriceL;
                buyPrice = p.previousPriceH;
                sellInstrument = p.shortInstrument;
                buyInstrument = p.longInstrument;
            }
        }

        if (buyPrice != 0.0 && sellPrice != 0.0) {
            auto r = Record::Ptr::create();
            r->setBidId(6666);
            r->setAskId(0);
            r->setBidOrAsk(Record::BidAsk::Bid);
            r->setDate(trade.date());
            r->setTime(trade.time());
            r->setInstrument(buyInstrument);
            r->setType(Record::Type::ENTER);
            r->setPrice(buyPrice);
            r->setVolume(50);
            r->setValue(r->price() * r->volume());
            emit newRecordCreated(r);
            qDebug() << "created a bid";

            r = Record::Ptr::create();
            r->setAskId(6666);
            r->setBidId(0);
            r->setBidOrAsk(Record::BidAsk::Ask);
            r->setDate(trade.date());
            r->setTime(trade.time());
            r->setInstrument(sellInstrument);
            r->setType(Record::Type::ENTER);
            r->setPrice(sellPrice);
            r->setVolume(50);
            r->setValue(r->price() * r->volume());
            emit newRecordCreated(r);
            qDebug() << "created a ask";
        }

        p.previousSpread = currentSpread;
        p.historicalSpread =  (1 / p.historySize * currentSpread) + p.historicalSpread;

    }

    /*

    double diff = trade.price();

    historicalSpread = 1 / (historySize + 1) *
    previousHistory
    currentHistory

    currentHistory = 1 / (n+1) * newval + prev_avg
    if (long - short > currentHistory)
     if (currentHistory < previousHistory) {
      sell long
     }
    }

    previousHistory = currentHistory;
    */
}
