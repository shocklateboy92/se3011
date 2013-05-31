#ifndef PAIRTRADINGSTRATEGY_H
#define PAIRTRADINGSTRATEGY_H

#include "pairtradingstrategy_global.h"
#include <trading-strategy.h>
#include <QtPlugin>

class PAIRTRADINGSTRATEGYSHARED_EXPORT PairTradingStrategy
        : public QObject, TradingStrategy
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID G8_STRATEGY_TYPE_ID)
    Q_INTERFACES(TradingStrategy)

public:
    PairTradingStrategy(QObject *parent = 0);

    QDockWidget* configWidget();

    void processTrade(const Trade &trade);

    class PairData;

    void reset();

 signals:
    void newRecordCreated(Record::Ptr r);

private slots:
    void processPair(const PairData pd);
    void removePair(const PairData pd);

private:

    QList<PairData> m_pairs;


};

class PairTradingStrategy::PairData {
public:

        double historicalSpread;
        double previousSpread;
        double previousPriceH;
        double previousPriceL;
        long long historySize;

        bool isRising;
        bool isFalling;
        bool bought;
        bool sold;
        QByteArray longInstrument;
        QByteArray shortInstrument;

        PairData() = default;

        PairData(QByteArray li, QByteArray si) :
            historicalSpread(0.0),
            previousPriceH(0.0),
            previousPriceL(0.0),
            isRising(false),
            isFalling(false),
            bought(false),
            sold(false),
            longInstrument(li),
            shortInstrument(si)
        {}

        bool operator== (const PairData &other) {
            return (longInstrument==other.longInstrument
                    && shortInstrument==other.shortInstrument);
        }

};

#endif // PAIRTRADINGSTRATEGY_H
