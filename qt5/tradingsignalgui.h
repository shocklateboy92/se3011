#ifndef TRADINGSIGNALGUI_H
#define TRADINGSIGNALGUI_H

namespace Ui {
class TradingSignalGUI;
}

class TradingSignalGUI : public QTabWidget
{
    Q_OBJECT

public:
    explicit TradingSignalGUI(QWidget *parent = 0);
    ~TradingSignalGUI();


private slots:
    void on_pushButton_3_clicked();

private:
    Ui::TradingSignalGUI *ui;
};

#endif // TRADINGSIGNALGUI_H
