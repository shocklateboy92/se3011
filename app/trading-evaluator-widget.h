#ifndef TRADINGEVALUATORWIDGET_H
#define TRADINGEVALUATORWIDGET_H

#include <QDockWidget>
#include <QAbstractTableModel>
#include <QDateTime>
#include <trading-evaluator.h>

namespace Ui {
class TradingEvaluatorWidget;
}

class TradingEvaluatorWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit TradingEvaluatorWidget(QAbstractTableModel *my, QAbstractTableModel *all,QWidget *parent = 0);
    ~TradingEvaluatorWidget();

public slots:
    void printCurrentEval(TradingEvaluator::eval e);

private:
    QAbstractTableModel *all_model;
    QAbstractTableModel *my_model;
    Ui::TradingEvaluatorWidget *ui;
};

#endif // TRADINGEVALUATORWIDGET_H
