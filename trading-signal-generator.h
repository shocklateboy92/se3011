#ifndef TRADINGSIGNALGENERATOR_H
#define TRADINGSIGNALGENERATOR_H

#include "record.h"
#include <tuple>

#include <QObject>
#include <QList>
#include <QMap>

class TradingSignalGenerator : public QObject
{
    Q_OBJECT
public:
    explicit TradingSignalGenerator(QObject *parent = 0);

signals:
    void newRecordGenerated(const Record &r);
    void nextRecord(const Record &r);

public slots:
    void processNewRecord(const Record &r);
    void processMomentum(const QString &instrument, const QString &volume, const QString &change);
    void dataProcessingRequested();
    void processTrade(const Trade &t);

private:
    class MomentumData;

    QList<Record> m_records;
    QMap<QString, MomentumData> m_momentums;
};

class TradingSignalGenerator::MomentumData {
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

#endif // TRADINGSIGNALGENERATOR_H
