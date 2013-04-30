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
    void processMomentum(const QString &instrument, const QString &change);
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
    int currentConsecutiveChanges;
    int consecutiveChangesRequired;
    double tradeVolume;

    MomentumData() :
        isRising(false),
        previousPrice(std::numeric_limits<double>::max()),
        currentConsecutiveChanges(-1),
        consecutiveChangesRequired(7),
        tradeVolume(25)
    {}
};

#endif // TRADINGSIGNALGENERATOR_H
