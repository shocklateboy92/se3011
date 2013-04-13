#include "main-window.h"
#include "ui_main-window.h"
#include "trading-file-reader.h"

#include <QAction>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_reader(new TradingFileReader(this))
{
    ui->setupUi(this);

    connect(ui->actionStart, &QAction::triggered, [&]() {
        QFile file("preview.csv");
        file.open(QIODevice::ReadOnly);
        QTextStream stream(&file);
        m_reader->startReading(stream);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
