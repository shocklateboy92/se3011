#include "main-window.h"
#include "ui_main-window.h"
#include "trading-file-reader.h"
#include <trading-files-model.h>
#include "trading-files-widget.h"
#include "trading-signal-results-widget.h"
#include "trading-evaluator-widget.h"
#include "trading-evaluator-graph.h"
#include "trading-signal-widget.h"
#include "trading-signal-generator.h"
#include "trading-signal-group-08.h"

#include "records-model.h"

#include <QAction>
#include <QFile>
#include <QThread>
#include <QtConcurrent/QtConcurrent>
#include <QTableView>
#include <QPaintEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_engineThread(new QThread(this)),
    m_evaluatorThread(new QThread(this)),
    m_signal_generatorThread(new QThread(this)),
    m_inputThread(new QThread(this)),
    m_engine(new TradingEngine()),
    m_evaluator(new TradingEvaluator()),
    m_signal_generator(new TradingSignalGenerator()),
    m_inputModel(new TradingFilesModel())
{
    ui->setupUi(this);

    setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::North);

    m_engine->moveToThread(m_engineThread);
    m_inputModel->moveToThread(m_inputThread);
    m_evaluator->moveToThread(m_evaluatorThread);
    m_signal_generator->moveToThread(m_signal_generatorThread);


    m_engineThread->start();
    m_inputThread->start();
    m_evaluatorThread->start();
    m_signal_generatorThread->start();

    addDockWidget(Qt::LeftDockWidgetArea,
                  new TradingFilesWidget(m_inputModel, this));

    m_signal_generator->loadPlugins();
    for (QDockWidget *widget : m_signal_generator->configWidgets()) {
        qDebug() << widget;
        addDockWidget(Qt::RightDockWidgetArea, widget, Qt::Vertical);
    }

    auto results = new RecordsModel(this);
    auto resultsWidget = new TradingSignalResultsWidget(results, this);
    addDockWidget(Qt::RightDockWidgetArea, resultsWidget);
    auto magic = new TradingSignalGroup08(this);
    addDockWidget(Qt::RightDockWidgetArea, magic);


    auto mytrades = new RecordsModel(this);
    auto alltrades = new RecordsModel(this);
    auto evalwidget = new TradingEvaluatorWidget(mytrades, alltrades, this);
    addDockWidget(Qt::BottomDockWidgetArea, evalwidget);

    auto graph = new TradingEvaluatorGraph(this);
    addDockWidget(Qt::BottomDockWidgetArea, graph);

    tabifyDockWidget(evalwidget, graph);

    connect(m_inputModel, &TradingFilesModel::newRecordEncountered,
            m_engine, &TradingEngine::processNewRecord);
    connect(m_engine, &TradingEngine::newTradeCreated,
            m_evaluator, &TradingEvaluator::processNewTrade);

    connect(ui->actionStart, &QAction::triggered, m_inputModel,
            &TradingFilesModel::dataProcessingRequested);
    connect(ui->actionStart, &QAction::triggered, m_signal_generator,
            &TradingSignalGenerator::dataProcessingRequested);

    connect(m_signal_generator, &TradingSignalGenerator::nextRecord,
            m_engine, &TradingEngine::processNewRecord);

    connect(ui->centralwidget, &TradingSignalWidget::newRecordCreated,
            m_signal_generator, &TradingSignalGenerator::processNewRecord);

    connect(m_signal_generator, &TradingSignalGenerator::newRecordGenerated,
            results, &RecordsModel::addRecord);

    connect(magic, &TradingSignalGroup08::newMagic, m_signal_generator, &TradingSignalGenerator::processMagic);
    connect(magic, &TradingSignalGroup08::deleteMagic, m_signal_generator, &TradingSignalGenerator::removeMagic);

    connect(m_engine, &TradingEngine::newTradeCreated,m_signal_generator, &TradingSignalGenerator::processTrade);


    //This is really slow
    //connect(m_engine, &TradingEngine::newTradeCreated, alltrades, &RecordsModel::addRecord);
    connect(m_evaluator, &TradingEvaluator::signalTradeEncountered, mytrades, &RecordsModel::addRecord);

    connect(m_evaluator, &TradingEvaluator::currentEval, evalwidget, &TradingEvaluatorWidget::printCurrentEval);

    connect(m_evaluator, &TradingEvaluator::signalTradeEncountered, graph, &TradingEvaluatorGraph::plotNew);

    m_overlay = new Overlay(this);
    m_overlay->setVisible(false);
}

MainWindow::~MainWindow()
{
    m_engineThread->quit();
    m_evaluatorThread->quit();
    m_signal_generatorThread->quit();
    m_inputThread->quit();

    m_engineThread->wait();
    m_evaluatorThread->wait();
    m_signal_generatorThread->wait();
    m_inputThread->wait();

    m_engine->deleteLater();
    m_evaluator->deleteLater();
    m_signal_generator->deleteLater();
    m_inputModel->deleteLater();

    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    m_overlay->resize(e->size());
    QWidget::resizeEvent(e);
}

void MainWindow::dropEvent(QDropEvent *e) {
    for (const QUrl &url : e->mimeData()->urls()) {
        if (url.isLocalFile() &&
                url.path().endsWith(QStringLiteral("g8strat"))) {
            QFileInfo f(url.toLocalFile());
            if (!QFile::copy(url.toLocalFile(),
                             QCoreApplication::applicationFilePath() +
                             QDir::separator() + f.fileName())) {
                qWarning() << "unable to install plugin" << url;
            }
        }
    }
    m_overlay->setVisible(false);
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls()) {
        for (const QUrl &url : e->mimeData()->urls()) {
            if (url.isLocalFile() &&
                    url.path().endsWith(QStringLiteral("g8strat"))) {
                e->acceptProposedAction();
                m_overlay->setVisible(true);
                break;
            }
        }
    }
}

void MainWindow::dragLeaveEvent(QDragLeaveEvent *e) {
    m_overlay->setVisible(false);
}
