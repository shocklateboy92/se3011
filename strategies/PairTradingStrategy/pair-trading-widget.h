#ifndef PAIRTRADINGWIDGET_H
#define PAIRTRADINGWIDGET_H

#include <QDockWidget>

namespace Ui {
class PairTradingWidget;
}

class PairTradingWidget : public QDockWidget
{
    Q_OBJECT
    
public:
    explicit PairTradingWidget(QWidget *parent = 0);
    ~PairTradingWidget();
    
private slots:
    void onAddtradeButtonClicked();

private:
    Ui::PairTradingWidget *ui;
};

#endif // PAIRTRADINGWIDGET_H
