#ifndef MANUALSTRATEGY_H
#define MANUALSTRATEGY_H

#include "manual_global.h"
#include <trading-strategy.h>
#include <QtPlugin>
#include <records-model.h>

class MANUALSHARED_EXPORT ManualStrategy
        : public QObject, TradingStrategy
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID G8_STRATEGY_TYPE_ID)
    Q_INTERFACES(TradingStrategy)
    
public:
    ManualStrategy(QObject *parent = 0);

    QDockWidget* configWidget();

    void processTrade(const Trade &trade);

signals:
    void newRecordCreated(Record::Ptr r);

private:
    RecordsModel *m_model;
    bool m_complete;
};

#endif // MANUALSTRATEGY_H
