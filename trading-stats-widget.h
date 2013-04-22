#ifndef TRADINGSTATSWIDGET_H
#define TRADINGSTATSWIDGET_H

#include <QWidget>

namespace Ui {
class TradingStatsWidget;
}

class TradingStatsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TradingStatsWidget(QWidget *parent = 0);
    ~TradingStatsWidget();

private:
    Ui::TradingStatsWidget *ui;
};

#endif // TRADINGSTATSWIDGET_H
