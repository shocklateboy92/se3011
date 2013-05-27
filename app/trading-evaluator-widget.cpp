#include "trading-evaluator-widget.h"
#include "ui_trading-evaluator-widget.h"

#include <QTableView>
#include <QDebug>

TradingEvaluatorWidget::TradingEvaluatorWidget(QAbstractTableModel *my, QAbstractTableModel *all,QWidget *parent) :
    QDockWidget(parent),all_model(my),my_model(all),
    ui(new Ui::TradingEvaluatorWidget)
{
    ui->setupUi(this);
    ui->my_trades->setModel(my);
}

TradingEvaluatorWidget::~TradingEvaluatorWidget()
{
    delete ui;
}

void TradingEvaluatorWidget::printCurrentEval(QList<TradingEvaluator::eval> evals) {
    ui->money_gained->setText(QString::number(evals.last().moneyGained));
    ui->money_spent->setText(QString::number(evals.last().moneySpent));
    ui->stocks_bought->setText(QString::number(evals.last().stocksPurchased));
    ui->stocks_sold->setText(QString::number(evals.last().stocksSold));
    ui->stocks_remaining->setText(QString::number(evals.last().stocksPurchased - evals.last().stocksSold));
    ui->profit->setText(QString::number(evals.last().moneyGained - evals.last().moneySpent));
}

