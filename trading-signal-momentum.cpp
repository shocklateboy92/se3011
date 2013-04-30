#include "trading-signal-momentum.h"
#include "ui_trading-signal-momentum.h"

TradingSignalMomentum::TradingSignalMomentum(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::TradingSignalMomentum)
{
    ui->setupUi(this);
    connect(ui->manualAdd, &QAbstractButton::clicked, this, &TradingSignalWidget::manualAddRecord);

}

TradingSignalMomentum::~TradingSignalMomentum()
{
    delete ui;
}

void TradingSignalMomentum::addMomentums() {

}
