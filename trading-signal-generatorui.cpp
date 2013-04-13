#include "tradingsignalgeneratorui.h"
#include "ui_tradingsignalgeneratorui.h"

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
