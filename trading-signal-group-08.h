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

signals:
    void newMagic(const QString &instrument);
    void deleteMagic(const QString &instrument);

public slots:
    void addMagic();
    void removeMagic();
    
private:
    Ui::TradingSignalGroup08 *ui;
};

#endif // TRADINGSIGNALGROUP08_H
