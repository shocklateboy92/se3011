#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "trading-engine.h"
#include "trading-evaluator.h"
#include "trading-file-reader.h"
#include "trading-signal-generator.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    TradingFileReader *m_reader;
    TradingEngine *m_engine;
    TradingEvaluator *m_evaluator;
};

#endif // MAINWINDOW_H
