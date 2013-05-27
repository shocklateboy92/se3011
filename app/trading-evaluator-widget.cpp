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

void TradingEvaluatorWidget::printCurrentEval(QDateTime datetime, float moneySpent, float moneyGained, float stocksSold, float stocksPurchased) {
    ui->money_gained->setText(QString::number(moneyGained));
    ui->money_spent->setText(QString::number(moneySpent));
    ui->stocks_bought->setText(QString::number(stocksPurchased));
    ui->stocks_sold->setText(QString::number(stocksSold));
    ui->stocks_remaining->setText(QString::number(stocksPurchased - stocksSold));
    ui->profit->setText(QString::number(moneyGained - moneySpent));
}

