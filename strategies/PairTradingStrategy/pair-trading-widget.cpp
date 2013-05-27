#include "pair-trading-widget.h"
#include "ui_pair-trading-widget.h"

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
