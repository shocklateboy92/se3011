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

void TradingEvaluatorWidget::printCurrentEval(TradingEvaluator::eval e) {
    ui->money_gained->setText(QString::number(e.moneyGained));
    ui->money_spent->setText(QString::number(e.moneySpent));
    ui->stocks_bought->setText(QString::number(e.stocksPurchased));
    ui->stocks_sold->setText(QString::number(e.stocksSold));
    ui->stocks_remaining->setText(QString::number(e.stocksPurchased - e.stocksSold));
    ui->profit->setText(QString::number(e.moneyGained - e.moneySpent));
}

void TradingEvaluatorWidget::reset()
{
    my_model->removeRows(0, my_model->rowCount());

    ui->money_gained->clear();
    ui->money_spent->clear();
    ui->stocks_bought->clear();
    ui->stocks_sold->clear();
    ui->stocks_remaining->clear();
    ui->profit->clear();
}
