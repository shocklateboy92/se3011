#include "main-window.h"
#include "ui_main-window.h"
#include "trading-file-reader.h"
#include "trading-files-model.h"
#include "trading-files-widget.h"
#include "trading-signal-results-widget.h"
#include "trading-evaluator-widget.h"
#include "trading-signal-widget.h"
#include "trading-signal-generator.h"
#include "records-model.h"

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
    m_signal_generatorThread(new QThread(this)),
    m_engine(new TradingEngine()),
    m_evaluator(new TradingEvaluator()),
    m_signal_generator(new TradingSignalGenerator())
{
    ui->setupUi(this);

    m_engine->moveToThread(m_engineThread);
    m_evaluator->moveToThread(m_evaluatorThread);
    m_signal_generator->moveToThread(m_signal_generatorThread);


    m_engineThread->start();
    m_evaluatorThread->start();
    m_signal_generatorThread->start();

    auto model = new TradingFilesModel(this);
    model->addSource("preview.csv");
    addDockWidget(Qt::LeftDockWidgetArea, new TradingFilesWidget(model, this));

    auto results = new RecordsModel(this);
    addDockWidget(Qt::RightDockWidgetArea,
                  new TradingSignalResultsWidget(results, this));

    auto mytrades = new RecordsModel(this);
    auto alltrades = new RecordsModel(this);
    addDockWidget(Qt::BottomDockWidgetArea,
                  new TradingEvaluatorWidget(mytrades, alltrades, this));

    connect(model, &TradingFilesModel::newRecordEncountered,
            m_engine, &TradingEngine::processNewRecord);
    connect(m_engine, &TradingEngine::newTradeCreated,
            m_evaluator, &TradingEvaluator::processNewTrade);

    //this is wrong as it isnt processing the signal generator
    connect(ui->actionStart, &QAction::triggered, model,
            &TradingFilesModel::dataProcessingRequested);


    connect(ui->centralwidget, &TradingSignalWidget::newRecordCreated,
            m_signal_generator, &TradingSignalGenerator::processNewRecord);

    connect(m_signal_generator, &TradingSignalGenerator::newRecordGenerated,
            results, &RecordsModel::addRecord);

    //this is probably wrong or not?
    connect(m_engine, &TradingEngine::newTradeCreated, alltrades, &RecordsModel::addRecord);
    connect(m_evaluator, &TradingEvaluator::signalTradeEncountered, mytrades, &RecordsModel::addRecord);

}

MainWindow::~MainWindow()
{
    m_engineThread->quit();
    m_evaluatorThread->quit();
    m_engine->deleteLater();
    m_evaluator->deleteLater();
    delete ui;
}
