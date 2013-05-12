#include "trading-signal-group-08.h"
#include "ui_trading-signal-group-08.h"

TradingSignalGroup08::TradingSignalGroup08(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::TradingSignalGroup08)
{
    ui->setupUi(this);
}

TradingSignalGroup08::~TradingSignalGroup08()
{
    delete ui;
}
