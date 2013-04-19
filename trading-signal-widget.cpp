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
    if(ui->type_dropdown->currentText() =="ENTER") {
        r.setType(Record::Type::ENTER);
    } else if (ui->type_dropdown->currentText() =="AMEND") {
        r.setType(Record::Type::AMEND);
    } else {
        r.setType(Record::Type::DELETE);
    }
    r.setPrice(ui->price_text->text().toDouble());
    r.setVolume(ui->quantity_text->text().toDouble());
    r.setValue(ui->price_text->text().toDouble()*ui->quantity_text->text().toDouble());
    if(ui->bid_ask_text->currentText() == "Bid") {
        r.setBidId(6666);
        r.setAskId(0);
        r.setBidOrAsk(Record::BidAsk::Bid);
    } else {
        r.setAskId(6666);
        r.setBidId(0);
        r.setBidOrAsk(Record::BidAsk::Ask);

    }
    r.setTransId(0);

    qDebug() <<r;
    emit newRecordCreated(r);
}


