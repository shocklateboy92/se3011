#ifndef TRADINGEVALUATORWIDGET_H
#define TRADINGEVALUATORWIDGET_H

#include <QDockWidget>
#include <QAbstractTableModel>

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
    void printCurrentEval(float moneySpent, float moneyGained);

private:
    QAbstractTableModel *all_model;
    QAbstractTableModel *my_model;
    Ui::TradingEvaluatorWidget *ui;
};

#endif // TRADINGEVALUATORWIDGET_H
