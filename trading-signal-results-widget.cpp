#include "trading-signal-results-widget.h"
#include "ui_trading-signal-results-widget.h"

#include <QTableView>

TradingSignalResultsWidget::TradingSignalResultsWidget(
        QAbstractTableModel *model, QWidget *parent) :
    QDockWidget(parent), m_model(model),
    ui(new Ui::TradingSignalResultsWidget)
{
    ui->setupUi(this);

    ui->tableView->setModel(model);
}

TradingSignalResultsWidget::~TradingSignalResultsWidget()
{
    delete ui;
}
