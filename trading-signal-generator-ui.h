#ifndef TRADINGSIGNALGENERATORUI_H
#define TRADINGSIGNALGENERATORUI_H

#include <QWidget>

namespace Ui {
class TradingSignalGeneratorUi;
}

class TradingSignalGeneratorUi : public QWidget
{
    Q_OBJECT
    
public:
    explicit TradingSignalGeneratorUi(QWidget *parent = 0);
    ~TradingSignalGeneratorUi();
    
private:
    Ui::TradingSignalGeneratorUi *ui;
};

#endif // TRADINGSIGNALGENERATORUI_H
