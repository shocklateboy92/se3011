#ifndef TRADINGSIGNALWIDGET_H
#define TRADINGSIGNALWIDGET_H

#include <QDockWidget>

namespace Ui {
class TradingSignalWidget;
}

class TradingSignalWidget : public QDockWidget
{
    Q_OBJECT
    
public:
    explicit TradingSignalWidget(QWidget *parent = 0);
    ~TradingSignalWidget();
    
private:
    Ui::TradingSignalWidget *ui;
};

#endif // TRADINGSIGNALWIDGET_H
