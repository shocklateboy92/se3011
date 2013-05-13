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



    //customPlot->graph(0)->setData(times, costs);
    // give the axes some labels:
    customPlot->xAxis->setLabel("Time");
    customPlot->yAxis->setLabel("Profit");
    // set axes ranges, so we see all data:
   // customPlot->xAxis->setRange(-1, 1);
    //customPlot->yAxis->setRange(0, 1);
    customPlot->replot();

}

TradingEvaluatorGraph::~TradingEvaluatorGraph()
{
    delete ui;
}

void TradingEvaluatorGraph::plotNew(const Trade &trade)
{
    double time = trade.time().msec();
    double price = trade.price();
    costs.append(price);
    times.append(time);

    ui->dockWidgetContents->graph(0)->addData(time,price );

}
