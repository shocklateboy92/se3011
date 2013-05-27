#include "pair-trading-widget.h"
#include "ui_pair-trading-widget.h"
#include "pair-trading-strategy.h"

PairTradingWidget::PairTradingWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::PairTradingWidget)
{
    ui->setupUi(this);
}

PairTradingWidget::~PairTradingWidget()
{
    delete ui;
}


void PairTradingWidget::onAddtradeButtonClicked()
{
    PairTradingStrategy::PairData pair;
    pair.longInstrument   = ui->instrument1_Line->text().toLocal8Bit();
    pair.shortInstrument  = ui->instrument2_Line->text().toLocal8Bit();

    pair.historicalSpread = 0.0;
    pair.previousPriceH = 0.0;
    pair.previousPriceL = 0.0;
    pair.isRising = false;
    pair.isFalling = false;
    pair.bought = false;
    pair.sold = false;


}
