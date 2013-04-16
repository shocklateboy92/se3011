#ifndef TRADINGSIGNALRESULTSWIDGET_H
#define TRADINGSIGNALRESULTSWIDGET_H

#include <QDockWidget>

namespace Ui {
class TradingSignalResultsWidget;
}

class TradingSignalResultsWidget : public QDockWidget
{
    Q_OBJECT
    
public:
    explicit TradingSignalResultsWidget(QWidget *parent = 0);
    ~TradingSignalResultsWidget();
    
private:
    Ui::TradingSignalResultsWidget *ui;
};

#endif // TRADINGSIGNALRESULTSWIDGET_H
