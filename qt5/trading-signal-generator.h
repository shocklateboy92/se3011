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
    void newRecordGenerated(Record &r);
public slots:

};

#endif // TRADINGSIGNALGENERATOR_H
