#ifndef TRADINGSIGNALRESULTSWIDGET_H
#define TRADINGSIGNALRESULTSWIDGET_H

#include <QDockWidget>
#include <QAbstractTableModel>
#include <records-model.h>

namespace Ui {
class TradingSignalResultsWidget;
}

class TradingSignalResultsWidget : public QDockWidget
{
    Q_OBJECT
    
public:
    explicit TradingSignalResultsWidget(RecordsModel *model,
                                        QWidget *parent = 0);
    ~TradingSignalResultsWidget();
    
private slots:
    void onRemovebuttonClicked();

private:
    QAbstractTableModel *m_model;
    Ui::TradingSignalResultsWidget *ui;
};

#endif // TRADINGSIGNALRESULTSWIDGET_H
