#include "trading-signal-results-widget.h"
#include "ui_trading-signal-results-widget.h"

#include <QDebug>
#include <QTableView>

TradingSignalResultsWidget::TradingSignalResultsWidget(
        RecordsModel *model, QWidget *parent) :
    QDockWidget(parent), m_model(model),
    ui(new Ui::TradingSignalResultsWidget)
{
    ui->setupUi(this);

    ui->tableView->setModel(model);
    connect(ui->removeButton, &QAbstractButton::clicked,
            this, &TradingSignalResultsWidget::onRemovebuttonClicked);

    connect(ui->form, &TradingSignalWidget::newRecordCreated,
            model, &RecordsModel::addRecord);
}

TradingSignalResultsWidget::~TradingSignalResultsWidget()
{
    delete ui;
}


void TradingSignalResultsWidget::onRemovebuttonClicked()
{
    qDebug();
    auto indexes = ui->tableView->selectionModel()->selection().indexes();
    if (!indexes.isEmpty()) {
        m_model->removeRow(indexes.first().row());
    }
}
