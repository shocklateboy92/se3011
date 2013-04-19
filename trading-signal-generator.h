#ifndef TRADINGSIGNALGENERATOR_H
#define TRADINGSIGNALGENERATOR_H

#include "record.h"

#include <QObject>
#include <QList>

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
    void dataProcessingRequested();

private:
    QList<Record> m_records;

};

#endif // TRADINGSIGNALGENERATOR_H
