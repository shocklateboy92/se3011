#ifndef TRADINGSIGNALGROUP08_H
#define TRADINGSIGNALGROUP08_H

#include <QDockWidget>

namespace Ui {
class TradingSignalGroup08;
}

class TradingSignalGroup08 : public QDockWidget
{
    Q_OBJECT
    
public:
    explicit TradingSignalGroup08(QWidget *parent = 0);
    ~TradingSignalGroup08();
    
private:
    Ui::TradingSignalGroup08 *ui;
};

#endif // TRADINGSIGNALGROUP08_H
