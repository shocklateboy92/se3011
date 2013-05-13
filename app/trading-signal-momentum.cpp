#include "trading-signal-momentum.h"
#include "ui_trading-signal-momentum.h"

TradingSignalMomentum::TradingSignalMomentum(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::TradingSignalMomentum)
{
    ui->setupUi(this);
    connect(ui->momentum_add, &QAbstractButton::clicked,
            this, &TradingSignalMomentum::addMomentum);
    connect(ui->removeButton, &QAbstractButton::clicked,
            this, &TradingSignalMomentum::onPushbuttonClicked);
}

TradingSignalMomentum::~TradingSignalMomentum()
{
    delete ui;
}

void TradingSignalMomentum::addMomentum() {
    QTableWidgetItem* instrument = new QTableWidgetItem(ui->instrument_text->text());
    QTableWidgetItem* volume = new QTableWidgetItem(ui->volume_text->text());
    QTableWidgetItem* change = new QTableWidgetItem(ui->change_text->text());

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, instrument);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, volume);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2, change);

    emit newMomentum(ui->instrument_text->text(), ui->volume_text->text(), ui->change_text->text());

    ui->instrument_text->clear();
    ui->volume_text->clear();
    ui->change_text->clear();
}

void TradingSignalMomentum::onPushbuttonClicked()
{
    QModelIndexList indexes = ui->tableWidget->selectionModel()
                                ->selection().indexes();
    if (!indexes.isEmpty()) {
        emit deleteMomentum(ui->tableWidget->selectedItems().first()->text());
        ui->tableWidget->removeRow(indexes.first().row());

    }
}
