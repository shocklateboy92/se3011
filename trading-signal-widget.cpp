#include "trading-signal-widget.h"
#include "ui_trading-signal-widget.h"
#include "record.h"
#include <QDebug>

TradingSignalWidget::TradingSignalWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TradingSignalWidget)
{
    ui->setupUi(this);
    connect(ui->manualAdd, &QAbstractButton::clicked, this, &TradingSignalWidget::manualAddRecord);
}

TradingSignalWidget::~TradingSignalWidget()
{
    delete ui;
}

void TradingSignalWidget::manualAddRecord() {
    Record r;
    r.setInstrument(ui->company_text->text());
    r.setDate(ui->time_text->date());
    r.setTime(ui->time_text->time());
    //r.setType(ui->type_dropdown->currentText());
    r.setPrice(ui->price_text->text().toDouble());
    r.setVolume(ui->quantity_text->text().toDouble());
    r.setValue(ui->price_text->text().toDouble()*ui->quantity_text->text().toDouble());
    if(ui->bid_ask_text->currentText() == "Bid") {
        r.setBidId(6666);
    } else {
        r.setAskId(6666);
    }
    qDebug() <<r;
    emit newRecordCreated(r);
}
