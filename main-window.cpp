#include "main-window.h"
#include "ui_main-window.h"
#include "trading-file-reader.h"

#include <QAction>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_reader(new TradingFileReader(this)),
    m_engine(new TradingEngine(this)),
    m_evaluator(new TradingEvaluator(this))
{
    ui->setupUi(this);

    connect(ui->actionStart, &QAction::triggered, [&]() {
        QFile file("preview.csv");
        file.open(QIODevice::ReadOnly);
        QTextStream stream(&file);
        m_reader->startReading(stream);
    });
    connect(m_reader, &TradingFileReader::newRecordEncountered,
            m_engine, &TradingEngine::processNewRecord);
    connect(m_engine, &TradingEngine::newTradeCreated,
            m_evaluator, &TradingEvaluator::processNewTrade);
}

MainWindow::~MainWindow()
{
    delete ui;
}
