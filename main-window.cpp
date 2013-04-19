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
    addDockWidget(Qt::LeftDockWidgetArea, new TradingFilesWidget(model, this));

    auto results = new RecordsModel(this);
    addDockWidget(Qt::RightDockWidgetArea,
                  new TradingSignalResultsWidget(results, this));

    auto mytrades = new RecordsModel(this);
    auto alltrades = new RecordsModel(this);
    auto evalwidget = new TradingEvaluatorWidget(mytrades, alltrades, this);
    addDockWidget(Qt::BottomDockWidgetArea,evalwidget);

    connect(model, &TradingFilesModel::newRecordEncountered,
            m_engine, &TradingEngine::processNewRecord);
    connect(m_engine, &TradingEngine::newTradeCreated,
            m_evaluator, &TradingEvaluator::processNewTrade);

    connect(ui->actionStart, &QAction::triggered, model,
            &TradingFilesModel::dataProcessingRequested);
    connect(ui->actionStart, &QAction::triggered, m_signal_generator,
            &TradingSignalGenerator::dataProcessingRequested);

    //this crashes why?
    connect(m_signal_generator, &TradingSignalGenerator::nextRecord,m_engine, &TradingEngine::processNewRecord);

    connect(ui->centralwidget, &TradingSignalWidget::newRecordCreated,
            m_signal_generator, &TradingSignalGenerator::processNewRecord);

    connect(m_signal_generator, &TradingSignalGenerator::newRecordGenerated,
            results, &RecordsModel::addRecord);

    //This is really slow
    connect(m_engine, &TradingEngine::newTradeCreated, alltrades, &RecordsModel::addRecord);
    connect(m_evaluator, &TradingEvaluator::signalTradeEncountered, mytrades, &RecordsModel::addRecord);

    connect(m_evaluator, &TradingEvaluator::currentEval, evalwidget, &TradingEvaluatorWidget::printCurrentEval);


}

MainWindow::~MainWindow()
{
    m_engineThread->quit();
    m_evaluatorThread->quit();
    m_signal_generatorThread->quit();
    m_engine->deleteLater();
    m_evaluator->deleteLater();
    m_signal_generator->deleteLater();
    delete ui;
}
