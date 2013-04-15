#include "trading-files-widget.h"
#include "ui_trading-files-widget.h"

#include <QTableView>

TradingFilesWidget::TradingFilesWidget(
        TradingFilesModel *m_model, QWidget *parent) :
    model(m_model), QDockWidget(parent),
    ui(new Ui::TradingFilesWidget)
{
    ui->setupUi(this);
    ui->tableView->setModel(model);
}

TradingFilesWidget::~TradingFilesWidget()
{
    delete ui;
}
