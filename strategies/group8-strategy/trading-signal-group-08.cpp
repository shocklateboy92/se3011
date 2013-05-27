#include "trading-signal-group-08.h"
#include "ui_trading-signal-group-08.h"

#include <QDebug>


TradingSignalGroup08::TradingSignalGroup08(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::TradingSignalGroup08)
{
    ui->setupUi(this);

    connect(ui->add_btn, &QAbstractButton::clicked,
            this, &TradingSignalGroup08::addMagic);
    connect(ui->delete_btn, &QAbstractButton::clicked,
            this, &TradingSignalGroup08::removeMagic);
}

TradingSignalGroup08::~TradingSignalGroup08()
{
    delete ui;
}


void TradingSignalGroup08::addMagic() {
    QTableWidgetItem* instrument = new QTableWidgetItem(ui->instrument_text->text());

    ui->instrument_table->insertRow(ui->instrument_table->rowCount());
    ui->instrument_table->setItem(ui->instrument_table->rowCount()-1, 0, instrument);

    emit newMagic(ui->instrument_text->text());

    ui->instrument_text->clear();
}

void TradingSignalGroup08::removeMagic()
{
    QModelIndexList indexes = ui->instrument_table->selectionModel()
                                ->selection().indexes();


    if (!indexes.isEmpty()) {
        emit deleteMagic(ui->instrument_table->selectedItems().first()->text());
        ui->instrument_table->removeRow(indexes.first().row());


    }
}
