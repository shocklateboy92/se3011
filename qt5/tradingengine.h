#ifndef TRADINGENGINE_H
#define TRADINGENGINE_H

#include <QObject>

class Record;

class TradingEngine : public QObject
{
    Q_OBJECT
public:
    explicit TradingEngine(QObject *parent = 0);

signals:

public slots:
    void processNewRecord(const Record &r);

};

#endif // TRADINGENGINE_H
