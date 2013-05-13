#ifndef TRADINGEVALUATORGRAPH_H
#define TRADINGEVALUATORGRAPH_H

#include <QDockWidget>
#include <order.h>


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
    void plotNew(const Trade &trade);


private:
    Ui::TradingEvaluatorGraph *ui;
    QMap<QTime, float> *profits;
};

#endif // TRADINGEVALUATORGRAPH_H
