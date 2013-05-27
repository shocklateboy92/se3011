#ifndef TRADINGEVALUATORGRAPH_H
#define TRADINGEVALUATORGRAPH_H

#include <QDockWidget>
#include <QInputDialog>
#include <QLineEdit>
#include <QMenu>
#include <order.h>
#include "qcustomplot.h"


namespace Ui {
class TradingEvaluatorGraph;
}

class TradingEvaluatorGraph : public QDockWidget
{
    Q_OBJECT
    
public:
    explicit TradingEvaluatorGraph(QWidget *parent = 0);
    ~TradingEvaluatorGraph();

public slots:
    void plotNew(QDateTime datetime, float moneySpent, float moneyGained, float stocksSold, float stocksPurchased);

private slots:
  void titleDoubleClick();
  void axisLabelDoubleClick(QCPAxis* axis, QCPAxis::SelectablePart part);
  void legendDoubleClick(QCPLegend* legend, QCPAbstractLegendItem* item);
  void selectionChanged();
  void mousePress();
  void mouseWheel();
  void removeSelectedGraph();
  void removeAllGraphs();
  void contextMenuRequest(QPoint pos);
  void moveLegend();
  void graphClicked(QCPAbstractPlottable *plottable);

private:
    Ui::TradingEvaluatorGraph *ui;
    QVector<double> moneySpent;
    QVector<double> moneyGained;
    QVector<double> profit;

    QVector<double> times;
};

#endif // TRADINGEVALUATORGRAPH_H
