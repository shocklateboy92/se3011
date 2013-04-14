#include "main-window.h"
#include "ui_main-window.h"
#include "trading-file-reader.h"
#include "trading-files-model.h"

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


    connect(ui->actionStart, &QAction::triggered, [&]() {
        QtConcurrent::run([&](){
            TradingFileReader reader("preview.csv");
            connect(&reader, &TradingFileReader::newRecordEncountered,
                    m_engine, &TradingEngine::processNewRecord);
            reader.startReading();
        });
    });
    connect(m_engine, &TradingEngine::newTradeCreated,
            m_evaluator, &TradingEvaluator::processNewTrade);

    ui->filesView->setModel(new TradingFilesModel(this));
}

MainWindow::~MainWindow()
{
    m_engineThread->quit();
    m_evaluatorThread->quit();
    m_engine->deleteLater();
    m_evaluator->deleteLater();
    delete ui;
}
