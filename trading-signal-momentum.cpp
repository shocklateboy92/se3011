#include "trading-signal-momentum.h"
#include "ui_trading-signal-momentum.h"

TradingSignalMomentum::TradingSignalMomentum(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::TradingSignalMomentum)
{
    ui->setupUi(this);
    connect(ui->momentum_add, &QAbstractButton::clicked, this, &TradingSignalMomentum::addMomentum);

}

TradingSignalMomentum::~TradingSignalMomentum()
{
    delete ui;
}

void TradingSignalMomentum::addMomentum() {
    QTableWidgetItem* instrument = new QTableWidgetItem(ui->instrument_text->text());
    QTableWidgetItem* change = new QTableWidgetItem(ui->change_text->text());

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, instrument);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, change);
}
