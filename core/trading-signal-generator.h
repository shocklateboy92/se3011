#ifndef TRADINGSIGNALGENERATOR_H
#define TRADINGSIGNALGENERATOR_H

#include "record.h"
#include "order.h"
#include "trading-strategy.h"
#include <tuple>

#include <QObject>
#include <QList>
#include <QMap>
#include <QDockWidget>

class GROUP8_CORE TradingSignalGenerator : public QObject
{
    Q_OBJECT
public:
    explicit TradingSignalGenerator(QObject *parent = 0);
    const QList<QDockWidget*> configWidgets();

signals:
    void newRecordGenerated(const Record &r);
    void nextRecord(Record::Ptr r);

public slots:
    void processNewRecord(const Record &r);

    void dataProcessingRequested();
    void processTrade(const Trade &t);

    void processMagic(const QString &instrument);
    void removeMagic(const QString &instrument);

    void loadPlugins();
    QDockWidget *addNewPlugin(QString fileName);

private:
    class MagicData;

    QList<TradingStrategy*> m_strategies;

    QList<Record> m_records;
    QMap<QString, MagicData> m_magic;
};

class TradingSignalGenerator::MagicData {
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

#endif // TRADINGSIGNALGENERATOR_H
