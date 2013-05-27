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

    void loadPlugins();
    QDockWidget *addNewPlugin(QString fileName);

    void reset();

private:

    QList<TradingStrategy*> m_strategies;

    QList<Record> m_records;

};

#endif // TRADINGSIGNALGENERATOR_H
