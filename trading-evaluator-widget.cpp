#include "trading-evaluator-widget.h"
#include "ui_trading-evaluator-widget.h"

#include <QTableView>

TradingEvaluatorWidget::TradingEvaluatorWidget(QAbstractTableModel *my, QAbstractTableModel *all,QWidget *parent) :
    QDockWidget(parent),all_model(my),my_model(all),
    ui(new Ui::TradingEvaluatorWidget)
{
    ui->setupUi(this);
    ui->all_trades->setModel(all);
    ui->my_trades->setModel(my);
}

TradingEvaluatorWidget::~TradingEvaluatorWidget()
{
    delete ui;
}
