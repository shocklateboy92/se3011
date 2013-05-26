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

    QDockWidget* configWidget();

    void processTrade(const Trade &trade);

signals:
    void newRecordCreated(Record::Ptr r);

private slots:
    void processMomentum(const QString &instrument,
                         const QString &volume,
                         const QString &change);
    void removeMomentum(const QString &instrument);

private:
    class MomentumData;
    QMap<QString, MomentumData> m_momentums;
};

class MomentumStrategy::MomentumData {
public:
    bool isRising;
    double previousPrice;
    double previousVolume;
    double volume;
    int currentConsecutiveChanges;
    int consecutiveChangesRequired;
    bool bought;
    bool sold;

    MomentumData() :
        isRising(false),
        previousPrice(0),
        previousVolume(0),
        volume(0),
        currentConsecutiveChanges(-1),
        consecutiveChangesRequired(3),
        bought(false),
        sold(false)
    {}
};

#endif // MOMENTUMSTRATEGY_H
