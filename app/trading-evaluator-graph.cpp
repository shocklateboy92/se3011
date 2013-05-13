#include "trading-evaluator-graph.h"
#include "ui_trading-evaluator-graph.h"

TradingEvaluatorGraph::TradingEvaluatorGraph(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::TradingEvaluatorGraph)
{
    ui->setupUi(this);
}

TradingEvaluatorGraph::~TradingEvaluatorGraph()
{
    delete ui;
}
