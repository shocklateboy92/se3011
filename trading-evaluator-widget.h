#ifndef TRADINGEVALUATORWIDGET_H
#define TRADINGEVALUATORWIDGET_H

#include <QDockWidget>

namespace Ui {
class TradingEvaluatorWidget;
}

class TradingEvaluatorWidget : public QDockWidget
{
    Q_OBJECT
    
public:
    explicit TradingEvaluatorWidget(QWidget *parent = 0);
    ~TradingEvaluatorWidget();
    
private:
    Ui::TradingEvaluatorWidget *ui;
};

#endif // TRADINGEVALUATORWIDGET_H
