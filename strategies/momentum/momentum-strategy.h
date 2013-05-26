#ifndef MOMENTUMSTRATEGY_H
#define MOMENTUMSTRATEGY_H

#include "momentum_global.h"
#include <trading-strategy.h>
#include <QtPlugin>

class MOMENTUMSHARED_EXPORT MomentumStrategy
        : public QObject, TradingStrategy
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID G8_STRATEGY_TYPE_ID)
    Q_INTERFACES(TradingStrategy)

public:
    MomentumStrategy(QObject *parent = 0);

    QWidget* configWidget();

    void processTrade(const Trade &trade);
};


#endif // MOMENTUMSTRATEGY_H
