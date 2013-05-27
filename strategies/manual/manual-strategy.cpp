#include "manual-strategy.h"
#include "trading-signal-results-widget.h"

#include <QLayout>
#include "trading-signal-widget.h"

ManualStrategy::ManualStrategy(QObject *parent)
    : QObject(parent),
      m_model(new RecordsModel(this)),
      m_complete(false)
{
}

QDockWidget *ManualStrategy::configWidget()
{
    return new TradingSignalResultsWidget(m_model);
}

void ManualStrategy::processTrade(const Trade &trade)
{
    Q_UNUSED(trade);

    if (!m_complete) {
        for (Record r : m_model->records()) {
            emit newRecordCreated(Record::Ptr(&r));
        }
        m_complete = true;
    }
}
