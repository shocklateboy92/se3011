#include "trading-evaluator-widget.h"
#include "ui_trading-evaluator-widget.h"

TradingEvaluatorWidget::TradingEvaluatorWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::TradingEvaluatorWidget)
{
    ui->setupUi(this);
}

TradingEvaluatorWidget::~TradingEvaluatorWidget()
{
    delete ui;
}
