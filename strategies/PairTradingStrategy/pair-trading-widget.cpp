#include "pair-trading-widget.h"
#include "ui_pair-trading-widget.h"
#include "pair-trading-strategy.h"
#include <QAbstractButton>

PairTradingWidget::PairTradingWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::PairTradingWidget)
{
    ui->setupUi(this);
    connect(ui->AddTrade_Button, &QAbstractButton::clicked,
            this, &PairTradingWidget::onAddtradeButtonClicked);
    connect(ui->RemoveTrade_Button, &QAbstractButton::clicked,
            this, &PairTradingWidget::onRemovetradeButtonClicked);
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
    pair.previousSpread = 0.0;
    pair.previousPriceH = 0.0;
    pair.previousPriceL = 0.0;
    pair.historySize = 0;
    pair.isRising = false;
    pair.isFalling = false;
    pair.bought = false;
    pair.sold = false;

    emit newPair(pair);

    QTableWidgetItem* longa = new QTableWidgetItem(ui->instrument1_Line->text());
    QTableWidgetItem* shorta = new QTableWidgetItem(ui->instrument2_Line->text());

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, longa);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, shorta);

    ui->instrument1_Line->clear();
    ui->instrument2_Line->clear();


}

void PairTradingWidget::onRemovetradeButtonClicked()
{

    QModelIndexList indexes = ui->tableWidget->selectionModel()
                                ->selection().indexes();
    if (!indexes.isEmpty()) {

        PairTradingStrategy::PairData pair;

        pair.longInstrument   = ui->tableWidget->selectedItems()[0]->text().toLocal8Bit();
        pair.shortInstrument  = ui->tableWidget->selectedItems()[1]->text().toLocal8Bit();

        pair.historicalSpread = 0.0;
        pair.previousPriceH = 0.0;
        pair.previousPriceL = 0.0;
        pair.isRising = false;
        pair.isFalling = false;
        pair.bought = false;
        pair.sold = false;

        emit deletePair(pair);

        ui->tableWidget->removeRow(indexes.first().row());

    }






}
