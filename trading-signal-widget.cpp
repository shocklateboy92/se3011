#include "trading-signal-widget.h"
#include "ui_trading-signal-widget.h"

TradingSignalWidget::TradingSignalWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TradingSignalWidget)
{
    ui->setupUi(this);
}

TradingSignalWidget::~TradingSignalWidget()
{
    delete ui;
}

void TradingSignalWidget::manualAddRecord() {

}
