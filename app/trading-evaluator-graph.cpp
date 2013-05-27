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
    customPlot->addGraph();
    customPlot->addGraph();

    customPlot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));



    //customPlot->graph(0)->setData(times, profit);
    customPlot->graph(0)->setName("Profit");
    customPlot->graph(0)->setPen(QPen(QColor(255,0,0,255)));
    customPlot->graph(0)->setBrush(QBrush(QColor(255,0,0,120)));

    //customPlot->graph(1)->setData(times, moneySpent);
    customPlot->graph(1)->setName("Money Spent");
    customPlot->graph(1)->setPen(QPen(QColor(0,255,0,255)));
    customPlot->graph(1)->setBrush(QBrush(QColor(0,255,0,120)));


    //customPlot->graph(2)->setData(times, moneyGained);
    customPlot->graph(2)->setName("Money Gained");
    customPlot->graph(2)->setPen(QPen(QColor(0,0,255,255)));
    customPlot->graph(2)->setBrush(QBrush(QColor(0,0,255,120)));



    // give the axes some labels:
    customPlot->xAxis->setLabel("Date Time");
    customPlot->yAxis->setLabel("Amount $");
    // set axes ranges, so we see all data:
    double now = QDateTime::currentDateTime().toTime_t();
    customPlot->xAxis->setRangeLower(now);
    customPlot->yAxis->setRangeLower(0);

    customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    customPlot->xAxis->setDateTimeFormat("HH:mm:s\ndd/MM");
    customPlot->xAxis->setAutoTickStep(true);

    customPlot->xAxis2->setVisible(true);
    customPlot->yAxis2->setVisible(true);
    customPlot->xAxis2->setTicks(false);
    customPlot->yAxis2->setTicks(false);
    customPlot->xAxis2->setTickLabels(false);
    customPlot->yAxis2->setTickLabels(false);

    customPlot->setTitle("Statistics");
    customPlot->legend->setVisible(true);



    //interactions

    customPlot->setInteractions(QCustomPlot::iRangeDrag | QCustomPlot::iRangeZoom | QCustomPlot::iSelectAxes |
                                    QCustomPlot::iSelectLegend | QCustomPlot::iSelectPlottables | QCustomPlot::iSelectTitle);
    customPlot->setRangeDrag(Qt::Horizontal|Qt::Vertical);
    customPlot->setRangeZoom(Qt::Horizontal|Qt::Vertical);


    // connect slot that ties some axis selections together (especially opposite axes):
    connect(customPlot, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(customPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

    // make bottom and left axes transfer their ranges to top and right axes:
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

    // connect some interaction slots:
    connect(customPlot, SIGNAL(titleDoubleClick(QMouseEvent*)), this, SLOT(titleDoubleClick()));
    connect(customPlot, SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)), this, SLOT(axisLabelDoubleClick(QCPAxis*,QCPAxis::SelectablePart)));
    connect(customPlot, SIGNAL(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)), this, SLOT(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*)));

    // connect slot that shows a message in the status bar when a graph is clicked:
    connect(customPlot, SIGNAL(plottableClick(QCPAbstractPlottable*,QMouseEvent*)), this, SLOT(graphClicked(QCPAbstractPlottable*)));

    // setup policy and connect slot for context menu popup:
    customPlot->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(customPlot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));


    //end interactions



    customPlot->replot();

}



void TradingEvaluatorGraph::plotNew(QList<TradingEvaluator::eval> evals)
{

    auto customPlot = ui->dockWidgetContents;

    for(TradingEvaluator::eval eval : evals) {

        double time = eval.datetime.toTime_t();
        double moneySpent = eval.moneySpent;
        double moneyGained = eval.moneyGained;

        if(moneySpent > lastSpent && time > lastTime) {
            customPlot->graph(1)->addData(time,moneySpent);
            customPlot->graph(0)->addData(time, (moneyGained-moneySpent));
            //qDebug() << "MoneySpent:" << moneySpent;
            lastSpent = moneySpent;
        }

        if(moneyGained > lastGained && time > lastTime) {
            customPlot->graph(2)->addData(time, moneyGained);
            customPlot->graph(0)->addData(time, (moneyGained-moneySpent));
            //qDebug() << "moneyGained:" << moneyGained;
            lastGained = moneyGained;
        }



        if(customPlot->xAxis->range().upper >= time) {
                    customPlot->xAxis->setRangeUpper(time + 1.0);
         }

        if(customPlot->xAxis->range().lower < time) {
                    customPlot->xAxis->setRangeLower(time);
        }
    }
    customPlot->rescaleAxes();
    customPlot->replot();

}




void TradingEvaluatorGraph::titleDoubleClick()
{
  // Set the plot title by double clicking on it

  bool ok;
  QString newTitle = QInputDialog::getText(this, "QCustomPlot example", "New plot title:", QLineEdit::Normal, ui->dockWidgetContents->title(), &ok);
  if (ok)
  {
    ui->dockWidgetContents->setTitle(newTitle);
    ui->dockWidgetContents->replot();
  }
}

void TradingEvaluatorGraph::axisLabelDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part)
{
  // Set an axis label by double clicking on it

  if (part == QCPAxis::spAxisLabel) // only react when the actual axis label is clicked, not tick label or axis backbone
  {
    bool ok;
    QString newLabel = QInputDialog::getText(this, "QCustomPlot example", "New axis label:", QLineEdit::Normal, axis->label(), &ok);
    if (ok)
    {
      axis->setLabel(newLabel);
      ui->dockWidgetContents->replot();
    }
  }
}

void TradingEvaluatorGraph::legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item)
{
  // Rename a graph by double clicking on its legend item

  Q_UNUSED(legend)
  if (item) // only react if item was clicked (user could have clicked on border padding of legend where there is no item, then item is 0)
  {
    QCPPlottableLegendItem *plItem = qobject_cast<QCPPlottableLegendItem*>(item);
    bool ok;
    QString newName = QInputDialog::getText(this, "QCustomPlot example", "New graph name:", QLineEdit::Normal, plItem->plottable()->name(), &ok);
    if (ok)
    {
      plItem->plottable()->setName(newName);
      ui->dockWidgetContents->replot();
    }
  }
}

void TradingEvaluatorGraph::selectionChanged()
{
  /*
   normally, axis base line, axis tick labels and axis labels are selectable separately, but we want
   the user only to be able to select the axis as a whole, so we tie the selected states of the tick labels
   and the axis base line together. However, the axis label shall be selectable individually.

   The selection state of the left and right axes shall be synchronized as well as the state of the
   bottom and top axes.

   Further, we want to synchronize the selection of the graphs with the selection state of the respective
   legend item belonging to that graph. So the user can select a graph by either clicking on the graph itself
   or on its legend item.
  */

  // make top and bottom axes be selected synchronously, and handle axis and tick labels as one selectable object:
  if (ui->dockWidgetContents->xAxis->selected().testFlag(QCPAxis::spAxis) || ui->dockWidgetContents->xAxis->selected().testFlag(QCPAxis::spTickLabels) ||
      ui->dockWidgetContents->xAxis2->selected().testFlag(QCPAxis::spAxis) || ui->dockWidgetContents->xAxis2->selected().testFlag(QCPAxis::spTickLabels))
  {
    ui->dockWidgetContents->xAxis2->setSelected(QCPAxis::spAxis|QCPAxis::spTickLabels);
    ui->dockWidgetContents->xAxis->setSelected(QCPAxis::spAxis|QCPAxis::spTickLabels);
  }
  // make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
  if (ui->dockWidgetContents->yAxis->selected().testFlag(QCPAxis::spAxis) || ui->dockWidgetContents->yAxis->selected().testFlag(QCPAxis::spTickLabels) ||
      ui->dockWidgetContents->yAxis2->selected().testFlag(QCPAxis::spAxis) || ui->dockWidgetContents->yAxis2->selected().testFlag(QCPAxis::spTickLabels))
  {
    ui->dockWidgetContents->yAxis2->setSelected(QCPAxis::spAxis|QCPAxis::spTickLabels);
    ui->dockWidgetContents->yAxis->setSelected(QCPAxis::spAxis|QCPAxis::spTickLabels);
  }

  // synchronize selection of graphs with selection of corresponding legend items:
  for (int i=0; i<ui->dockWidgetContents->graphCount(); ++i)
  {
    QCPGraph *graph = ui->dockWidgetContents->graph(i);
    QCPPlottableLegendItem *item = ui->dockWidgetContents->legend->itemWithPlottable(graph);
    if (item->selected() || graph->selected())
    {
      item->setSelected(true);
      graph->setSelected(true);
    }
  }
}

void TradingEvaluatorGraph::mousePress()
{
  // if an axis is selected, only allow the direction of that axis to be dragged
  // if no axis is selected, both directions may be dragged

  if (ui->dockWidgetContents->xAxis->selected().testFlag(QCPAxis::spAxis))
    ui->dockWidgetContents->setRangeDrag(ui->dockWidgetContents->xAxis->orientation());
  else if (ui->dockWidgetContents->yAxis->selected().testFlag(QCPAxis::spAxis))
    ui->dockWidgetContents->setRangeDrag(ui->dockWidgetContents->yAxis->orientation());
  else
    ui->dockWidgetContents->setRangeDrag(Qt::Horizontal|Qt::Vertical);
}

void TradingEvaluatorGraph::mouseWheel()
{
  // if an axis is selected, only allow the direction of that axis to be zoomed
  // if no axis is selected, both directions may be zoomed

  if (ui->dockWidgetContents->xAxis->selected().testFlag(QCPAxis::spAxis))
    ui->dockWidgetContents->setRangeZoom(ui->dockWidgetContents->xAxis->orientation());
  else if (ui->dockWidgetContents->yAxis->selected().testFlag(QCPAxis::spAxis))
    ui->dockWidgetContents->setRangeZoom(ui->dockWidgetContents->yAxis->orientation());
  else
    ui->dockWidgetContents->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

void TradingEvaluatorGraph::removeSelectedGraph()
{
  if (ui->dockWidgetContents->selectedGraphs().size() > 0)
  {
    ui->dockWidgetContents->removeGraph(ui->dockWidgetContents->selectedGraphs().first());
    ui->dockWidgetContents->replot();
  }
}

void TradingEvaluatorGraph::removeAllGraphs()
{
  ui->dockWidgetContents->clearGraphs();
  ui->dockWidgetContents->replot();
}

void TradingEvaluatorGraph::contextMenuRequest(QPoint pos)
{
  QMenu *menu = new QMenu(this);
  menu->setAttribute(Qt::WA_DeleteOnClose);

  if (ui->dockWidgetContents->legend->selectTestLegend(pos)) // context menu on legend requested
  {
    menu->addAction("Move to top left", this, SLOT(moveLegend()))->setData((int)QCPLegend::psTopLeft);
    menu->addAction("Move to top center", this, SLOT(moveLegend()))->setData((int)QCPLegend::psTop);
    menu->addAction("Move to top right", this, SLOT(moveLegend()))->setData((int)QCPLegend::psTopRight);
    menu->addAction("Move to bottom right", this, SLOT(moveLegend()))->setData((int)QCPLegend::psBottomRight);
    menu->addAction("Move to bottom left", this, SLOT(moveLegend()))->setData((int)QCPLegend::psBottomLeft);
  } else  // general context menu on graphs requested
  {
    if (ui->dockWidgetContents->selectedGraphs().size() > 0)
      menu->addAction("Remove selected graph", this, SLOT(removeSelectedGraph()));
    if (ui->dockWidgetContents->graphCount() > 0)
      menu->addAction("Remove all graphs", this, SLOT(removeAllGraphs()));
  }

  menu->popup(ui->dockWidgetContents->mapToGlobal(pos));
}

void TradingEvaluatorGraph::moveLegend()
{
  if (QAction* contextAction = qobject_cast<QAction*>(sender())) // make sure this slot is really called by a context menu action, so it carries the data we need
  {
    bool ok;
    int dataInt = contextAction->data().toInt(&ok);
    if (ok)
    {
      ui->dockWidgetContents->legend->setPositionStyle((QCPLegend::PositionStyle)dataInt);
      ui->dockWidgetContents->replot();
    }
  }
}

void TradingEvaluatorGraph::graphClicked(QCPAbstractPlottable *plottable)
{
  ui->dockWidgetContents->setTitle(QString("Statistics - %1").arg(plottable->name()));
}


TradingEvaluatorGraph::~TradingEvaluatorGraph()
{
    delete ui;
}
