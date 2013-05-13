#include "trading-evaluator-widget.h"
#include "ui_trading-evaluator-widget.h"

#include <QTableView>

TradingEvaluatorWidget::TradingEvaluatorWidget(QAbstractTableModel *my, QAbstractTableModel *all,QWidget *parent) :
    QDockWidget(parent),all_model(my),my_model(all),
    ui(new Ui::TradingEvaluatorWidget)
{
    ui->setupUi(this);
    //ui->all_trades->setModel(all);
    ui->my_trades->setModel(my);
}

TradingEvaluatorWidget::~TradingEvaluatorWidget()
{
    delete ui;
}

void TradingEvaluatorWidget::printCurrentEval(float moneySpent, float moneyGained, float stocksSold, float stocksPurchased) {
    ui->money_gained->text() = QString::number(moneyGained);
    ui->money_spent->text() = QString::number(moneySpent);
    ui->stocks_bought->text() = QString::number(stocksPurchased);
    ui->stocks_sold->text() = QString::number(stocksSold);
    ui->stocks_remaining->text() =  QString::number(stocksPurchased - stocksSold);
    ui->profit->text() =  QString::number(moneyGained - moneySpent);

}

