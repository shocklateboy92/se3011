#include "main-window.h"
#include "ui_main-window.h"
#include "trading-file-reader.h"
#include <trading-files-model.h>
#include "trading-files-widget.h"
#include "trading-evaluator-widget.h"
#include "trading-evaluator-graph.h"
#include "trading-signal-generator.h"
#include "trading-signal-group-08.h"

#include "records-model.h"

#include <QAction>
#include <QFile>
#include <QThread>
#include <QtConcurrent/QtConcurrent>
#include <QTableView>
#include <QPaintEvent>

void MainWindow::setupMenuView()
{
    for (QAction *action : ui->menuView->actions()) {
        ui->menuView->removeAction(action);
    }

    for (QDockWidget* dock : findChildren<QDockWidget*>()) {
        ui->menuView->addAction(dock->toggleViewAction());
    }
}

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

    QList<QDockWidget*> list = m_signal_generator->configWidgets();
    for (QDockWidget *widget : list) {
        qDebug() << widget;
        addDockWidget(Qt::RightDockWidgetArea, widget);
        if(list.first()!=widget) {
         tabifyDockWidget(list.first(),widget);
        }
    }

    if(!list.empty())
        list.first()->raise();


    auto mytrades = new RecordsModel(this);
    auto alltrades = new RecordsModel(this);
    auto evalwidget = new TradingEvaluatorWidget(mytrades, alltrades, this);
    addDockWidget(Qt::BottomDockWidgetArea, evalwidget);

    auto graph = new TradingEvaluatorGraph(this);
    addDockWidget(Qt::BottomDockWidgetArea, graph);

    tabifyDockWidget(evalwidget, graph);
    evalwidget->raise();

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

    connect(m_engine, &TradingEngine::newTradeCreated,m_signal_generator, &TradingSignalGenerator::processTrade);


    //This is really slow
    //connect(m_engine, &TradingEngine::newTradeCreated, alltrades, &RecordsModel::addRecord);
    connect(m_evaluator, &TradingEvaluator::signalTradeEncountered, mytrades, &RecordsModel::addRecord);

    connect(m_evaluator, &TradingEvaluator::latestEval, evalwidget, &TradingEvaluatorWidget::printCurrentEval);

    connect(m_evaluator, &TradingEvaluator::currentEval, graph, &TradingEvaluatorGraph::plotNew);

    m_overlay = new Overlay(this);
    m_overlay->setVisible(false);


    //the reset + bonus
        //ui stuff
        connect(ui->actionReset, &QAction::triggered, graph, &TradingEvaluatorGraph::reset);
        connect(ui->actionReset, &QAction::triggered, evalwidget, &TradingEvaluatorWidget::reset);
        //have to reset strategies
        connect(ui->actionReset, &QAction::triggered, m_signal_generator, &TradingSignalGenerator::reset);

        //core stuff
        connect(ui->actionReset, &QAction::triggered, m_evaluator, &TradingEvaluator::reset);
        connect(ui->actionReset, &QAction::triggered, m_engine, &TradingEngine::reset);

    //end reset

    setupMenuView();
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
            QString fname = url.toLocalFile();
            QFileInfo f(fname);
            QString dest = QCoreApplication::applicationDirPath() +
                    QDir::separator() + "strategies" +
                    QDir::separator() + f.fileName();
            if (!QFile::copy(fname, dest)) {
                qWarning() << "unable to install plugin" << url << "to" << dest;
            }
            QDockWidget* w = m_signal_generator->addNewPlugin(fname);
            if (w) {
                addDockWidget(Qt::RightDockWidgetArea, w);
                setupMenuView();
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
                m_overlay->raise();
                m_overlay->setVisible(true);
                break;
            }
        }
    }
}

void MainWindow::dragLeaveEvent(QDragLeaveEvent *e) {
    Q_UNUSED(e);
    m_overlay->setVisible(false);
}
