#include "trading-signal-results-widget.h"
#include "ui_trading-signal-results-widget.h"

TradingSignalResultsWidget::TradingSignalResultsWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::TradingSignalResultsWidget)
{
    ui->setupUi(this);
}

TradingSignalResultsWidget::~TradingSignalResultsWidget()
{
    delete ui;
}
