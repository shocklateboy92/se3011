#include "main-window.h"
#include "ui_main-window.h"
#include "trading-file-reader.h"
#include "trading-files-model.h"
#include "trading-files-widget.h"
#include "trading-signal-results-widget.h"
#include "trading-signal-widget.h"


#include <QAction>
#include <QFile>
#include <QThread>
#include <QtConcurrent/QtConcurrent>
#include <QTableView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_engineThread(new QThread(this)),
    m_evaluatorThread(new QThread(this)),
    m_engine(new TradingEngine()),
    m_evaluator(new TradingEvaluator())
{
    ui->setupUi(this);

    m_engine->moveToThread(m_engineThread);
    m_evaluator->moveToThread(m_evaluatorThread);

    m_engineThread->start();
    m_evaluatorThread->start();

    auto model = new TradingFilesModel(this);
    model->addSource("preview.csv");
    addDockWidget(Qt::LeftDockWidgetArea, new TradingFilesWidget(model, this));

    addDockWidget(Qt::RightDockWidgetArea, new TradingSignalResultsWidget(this));

    connect(model, &TradingFilesModel::newRecordEncountered,
            m_engine, &TradingEngine::processNewRecord);
    connect(m_engine, &TradingEngine::newTradeCreated,
            m_evaluator, &TradingEvaluator::processNewTrade);
    connect(ui->actionStart, &QAction::triggered, model,
            &TradingFilesModel::dataProcessingRequested);
}

MainWindow::~MainWindow()
{
    m_engineThread->quit();
    m_evaluatorThread->quit();
    m_engine->deleteLater();
    m_evaluator->deleteLater();
    delete ui;
}
