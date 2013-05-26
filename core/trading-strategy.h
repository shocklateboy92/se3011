#ifndef TRADINGSTRATEGY_H
#define TRADINGSTRATEGY_H

#include "order.h"

#include <QObject>
#include <QWidget>

class TradingStrategy : public QObject
{
Q_OBJECT

public:
    TradingStrategy(const QObject *parent = 0);
    virtual ~TradingStrategy(){}

    virtual QWidget* configWidget() = 0;

public slots:
    virtual void processTrade(const Trade& trade) = 0;
};

#endif // TRADINGSTRATEGY_H
