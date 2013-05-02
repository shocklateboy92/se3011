#include "trading-signal-results-widget.h"
#include "ui_trading-signal-results-widget.h"

#include <QDebug>
#include <QTableView>

TradingSignalResultsWidget::TradingSignalResultsWidget(
        QAbstractTableModel *model, QWidget *parent) :
    QDockWidget(parent), m_model(model),
    ui(new Ui::TradingSignalResultsWidget)
{
    ui->setupUi(this);

    ui->tableView->setModel(model);
    connect(ui->removeButton, &QAbstractButton::clicked,
            this, &TradingSignalResultsWidget::onRemovebuttonClicked);
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
