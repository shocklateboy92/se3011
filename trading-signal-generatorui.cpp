#include "trading-signal-generator-ui.h"
#include "ui_trading-signal-generator-ui.h"

TradingSignalGeneratorUi::TradingSignalGeneratorUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TradingSignalGeneratorUi)
{
    ui->setupUi(this);
}

TradingSignalGeneratorUi::~TradingSignalGeneratorUi()
{
    delete ui;
}

void TradingSignalGeneratorUi::manualAddRecord()
{
}
