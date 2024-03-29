#ifndef TRADINGSIGNALMOMENTUM_H
#define TRADINGSIGNALMOMENTUM_H

#include <QDockWidget>
#include "momentum_global.h"

namespace Ui {
class TradingSignalMomentum;
}

class MOMENTUMSHARED_EXPORT TradingSignalMomentum : public QDockWidget
{
    Q_OBJECT
    
public:
    explicit TradingSignalMomentum(QWidget *parent = 0);
    ~TradingSignalMomentum();

signals:
    void newMomentum(const QString &instrument, const QString &volume, const QString &change);
    void deleteMomentum(const QString &instrument);

public slots:
    void addMomentum();
    
private slots:
    void onPushbuttonClicked();

private:
    Ui::TradingSignalMomentum *ui;
};



#endif // TRADINGSIGNALMOMENTUM_H
