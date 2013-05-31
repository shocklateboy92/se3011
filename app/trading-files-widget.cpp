#include "trading-files-widget.h"
#include "ui_trading-files-widget.h"

#include <QDebug>
#include <QPushButton>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QUrl>
#include <QFileDialog>

TradingFilesWidget::TradingFilesWidget(TradingFilesModel *model,
                                       QWidget *parent) :
    QDockWidget(parent),
    m_model(model),
    ui(new Ui::TradingFilesWidget)
{
    ui->setupUi(this);
    ui->tableView->setModel(model);
    connect(ui->tableView->selectionModel(),
            &QItemSelectionModel::selectionChanged, this,
            &TradingFilesWidget::onSelectionChanged);

    connect(ui->removeButton, &QAbstractButton::clicked, this,
            &TradingFilesWidget::onRemovebuttonClicked);
    connect(ui->addButton, &QAbstractButton::clicked, this,
            &TradingFilesWidget::onAddbuttonClicked);
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

void TradingFilesWidget::dropEvent(QDropEvent *e) {
    qDebug() << e;
    for (QUrl url : e->mimeData()->urls()) {
        if (url.isLocalFile()) {
            m_model->addSource(QDir::toNativeSeparators(url.toLocalFile()));
        } else {
            qWarning() << "ignoring" << url << "becuase it's not a local file";
        }
    }
}

void TradingFilesWidget::dragEnterEvent(QDragEnterEvent *e) {
    qDebug() << e->mimeData()->text();
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}


void TradingFilesWidget::onAddbuttonClicked()
{
    auto files = QFileDialog::getOpenFileNames(
            this, "Choose a file to import",
            QString(), "CSV Files (*.csv);;All Files (*)"
    );

    for (QString file : files) {
        m_model->addSource(file);
    }
}
