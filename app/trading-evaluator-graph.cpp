#include "trading-evaluator-graph.h"
#include "ui_trading-evaluator-graph.h"

TradingEvaluatorGraph::TradingEvaluatorGraph(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::TradingEvaluatorGraph)
{
    ui->setupUi(this);

    auto customPlot = ui->dockWidgetContents;


    // create graph and assign data to it:
    customPlot->addGraph();



    customPlot->graph(0)->setData(times, costs);
    // give the axes some labels:
    customPlot->xAxis->setLabel("Time");
    customPlot->yAxis->setLabel("Profit");
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRangeLower(0);
    customPlot->yAxis->setRangeLower(0);
    customPlot->replot();

}

TradingEvaluatorGraph::~TradingEvaluatorGraph()
{
    delete ui;
}

void TradingEvaluatorGraph::plotNew(const Trade &trade)
{
    auto customPlot = ui->dockWidgetContents;

    double time = QTime().secsTo(trade.time());
    double price = trade.price();
    costs.append(price);
    times.append(time);
    qDebug() << "Should plot a point";
    qDebug() << trade.time();
    qDebug() << time;
    qDebug() << price;
    customPlot->graph(0)->addData(time,price);

    if(customPlot->yAxis->range().upper <= price) {
        customPlot->yAxis->setRangeUpper(price + 1.0);
    }

    if(customPlot->xAxis->range().upper <= time) {
        customPlot->xAxis->setRangeUpper(time + 1.0);
    }

//    ui->dockWidgetContents->graph(0)->addData(0.5,1.0 );
//    ui->dockWidgetContents->graph(0)->addData(0.5,0.5 );
//    ui->dockWidgetContents->graph(0)->addData(5.0,5.0 );

    ui->dockWidgetContents->replot();

}
