#ifndef TRADINGSIGNALMOMENTUM_H
#define TRADINGSIGNALMOMENTUM_H

#include <QDockWidget>

namespace Ui {
class TradingSignalMomentum;
}

class TradingSignalMomentum : public QDockWidget
{
    Q_OBJECT
    
public:
    explicit TradingSignalMomentum(QWidget *parent = 0);
    ~TradingSignalMomentum();

public slots:
    void addMomentum();
    
private:
    Ui::TradingSignalMomentum *ui;
};



#endif // TRADINGSIGNALMOMENTUM_H
