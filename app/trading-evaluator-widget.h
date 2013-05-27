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
    explicit TradingEvaluatorWidget(RecordsModel *my, RecordsModel *all,QWidget *parent = 0);
    ~TradingEvaluatorWidget();

public slots:
    void printCurrentEval(TradingEvaluator::eval e);
    void reset();

private:
    RecordsModel *all_model;
    RecordsModel *my_model;
    Ui::TradingEvaluatorWidget *ui;
};

#endif // TRADINGEVALUATORWIDGET_H
