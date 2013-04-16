#ifndef TRADINGSIGNALWIDGET_H
#define TRADINGSIGNALWIDGET_H

#include <QWidget>

class Record;

namespace Ui {
class TradingSignalWidget;
}

class TradingSignalWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit TradingSignalWidget(QWidget *parent = 0);
    ~TradingSignalWidget();


signals:
    void newRecordCreated(const Record &r);

public slots:
    void manualAddRecord();

private:
    Ui::TradingSignalWidget *ui;
};

#endif // TRADINGSIGNALWIDGET_H
