#include "manual-strategy.h"
#include "trading-signal-results-widget.h"

#include "trading-signal-widget.h"
#include <QDebug>

ManualStrategy::ManualStrategy(QObject *parent)
    : QObject(parent),
      m_model(new RecordsModel(this)),
      m_complete(false)
{
}

QDockWidget *ManualStrategy::configWidget()
{
    auto widget = new TradingSignalResultsWidget(m_model);
    return widget;
}

void ManualStrategy::processTrade(const Trade &trade)
{
    Q_UNUSED(trade);

    if (!m_complete) {
        for (const Record &r : m_model->records()) {
            qDebug() << "emiting manual trade:" << r;
            Record::Ptr rec = Record::Ptr::create();
            *rec = r;
            emit newRecordCreated(rec);
        }
        m_complete = true;
    }
}
