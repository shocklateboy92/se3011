#ifndef GROUP8STRATEGY_H
#define GROUP8STRATEGY_H

#include "group8-strategy_global.h"
#include <trading-strategy.h>
#include <QtPlugin>

class GROUP8STRATEGYSHARED_EXPORT Group8Strategy
        : public QObject, TradingStrategy
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID G8_STRATEGY_TYPE_ID)
    Q_INTERFACES(TradingStrategy)

public:
    Group8Strategy(QObject *parent = 0);

    QDockWidget* configWidget();

    void processTrade(const Trade &trade);

    void reset();

signals:
    void newRecordCreated(Record::Ptr r);

private slots:
    void processMagic(const QString &instrument);
    void removeMagic(const QString &instrument);

private:
    class MagicData;
    QMap<QString, MagicData> m_magic;
};


class Group8Strategy::MagicData {
public:
    bool isRising;
    double previousPrice;
    double previousVolume;
    int currentConsecutiveChanges;
    double totalBought;
    double totalSold;

    MagicData() :
        isRising(false),
        previousPrice(0),
        previousVolume(0),
        currentConsecutiveChanges(-1),
        totalBought(0),
        totalSold(0)
    {}
};


#endif // GROUP8STRATEGY_H
