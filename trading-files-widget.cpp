#include "trading-files-widget.h"
#include "ui_trading-files-widget.h"

#include <QDebug>
#include <QPushButton>

TradingFilesWidget::TradingFilesWidget(TradingFilesModel *model,
                                       QWidget *parent) :
    QDockWidget(parent),
    m_model(model),
    ui(new Ui::TradingFilesWidget)
{
    ui->setupUi(this);
    ui->tableView->setModel(model);
    connect(ui->tableView->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
            &TradingFilesWidget::onSelectionChanged);

    connect(ui->removeButton, &QAbstractButton::clicked, this,
            &TradingFilesWidget::onRemovebuttonClicked);
}

TradingFilesWidget::~TradingFilesWidget()
{
    delete ui;
}

void TradingFilesWidget::onSelectionChanged()
{
    qDebug() << ui->tableView->selectionModel()->selection().indexes();
    if (ui->tableView->selectionModel()->selection().indexes().isEmpty()) {
        ui->removeButton->setEnabled(false);
    } else {
        ui->removeButton->setEnabled(true);
    }
}

void TradingFilesWidget::onRemovebuttonClicked()
{
    qDebug();
    m_model->removeRow(ui->tableView->selectionModel()->
                       selection().indexes().first().row());
}
