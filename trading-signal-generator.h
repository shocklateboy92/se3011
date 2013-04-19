#ifndef TRADINGSIGNALGENERATOR_H
#define TRADINGSIGNALGENERATOR_H

#include <QObject>

class Record;

class TradingSignalGenerator : public QObject
{
    Q_OBJECT
public:
    explicit TradingSignalGenerator(QObject *parent = 0);

signals:
    void newRecordGenerated(const Record &r);

public slots:
    void processNewRecord(const Record &r);

};

#endif // TRADINGSIGNALGENERATOR_H
