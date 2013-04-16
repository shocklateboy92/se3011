#ifndef TRADINGSIGNALRESULTSWIDGET_H
#define TRADINGSIGNALRESULTSWIDGET_H

#include <QDockWidget>
#include <QAbstractTableModel>

namespace Ui {
class TradingSignalResultsWidget;
}

class TradingSignalResultsWidget : public QDockWidget
{
    Q_OBJECT
    
public:
    explicit TradingSignalResultsWidget(QAbstractTableModel *model,
                                        QWidget *parent = 0);
    ~TradingSignalResultsWidget();
    
private:
    QAbstractTableModel *m_model;
    Ui::TradingSignalResultsWidget *ui;
};

#endif // TRADINGSIGNALRESULTSWIDGET_H
