#ifndef PAIRTRADINGSTRATEGY_H
#define PAIRTRADINGSTRATEGY_H

#include "pairtradingstrategy_global.h"
#include <trading-strategy.h>
#include <QtPlugin>

class PAIRTRADINGSTRATEGYSHARED_EXPORT PairTradingStrategy
        : public QObject, TradingStrategy
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PAIR_TRADE_STRATEGY_TYPE_ID)
    Q_INTERFACES(TradingStrategy)

public:
    PairTradingStrategy(QObject *parent = 0);

    QDockWidget* configWidget();

    void processTrade(const Trade &trade);

 signals:
    void newRecordCreate(Record::Ptr r);

private slots:
    void processPair(const QString &instrument,
                         const QString &volume,
                         const QString &change);
    void removePair(const QString &instrument);

private:
    class PairData;
    QList<PairData> m_pairs;


};

class PairTradingStrategy::PairData {
public:
        double historicalSpread;
        double previousPrice1;
        double previousPrice2;
        bool bought;
        bool sold;




};

#endif // PAIRTRADINGSTRATEGY_H
