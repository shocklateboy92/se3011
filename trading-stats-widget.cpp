#include "trading-stats-widget.h"
#include "ui_trading-stats-widget.h"

TradingStatsWidget::TradingStatsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TradingStatsWidget)
{
    ui->setupUi(this);
}

TradingStatsWidget::~TradingStatsWidget()
{
    delete ui;
}
