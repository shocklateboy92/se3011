#ifndef TRADINGSTRATEGY_H
#define TRADINGSTRATEGY_H

#include "order.h"

#include <QObject>
#include <QWidget>
#include <QDockWidget>

class TradingStrategy
{

public:
    virtual ~TradingStrategy(){}

    virtual QDockWidget* configWidget() = 0;

    virtual void processTrade(const Trade& trade) = 0;
};

#define G8_STRATEGY_TYPE_ID "com.g8.tanya.strategy"
Q_DECLARE_INTERFACE(TradingStrategy, G8_STRATEGY_TYPE_ID)

#endif // TRADINGSTRATEGY_H
