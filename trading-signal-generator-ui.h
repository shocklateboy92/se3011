#ifndef TRADINGSIGNALGENERATORUI_H
#define TRADINGSIGNALGENERATORUI_H

#include <QWidget>

class Record;

namespace Ui {
class TradingSignalGeneratorUi;
}

class TradingSignalGeneratorUi : public QWidget
{
    Q_OBJECT

public:
    explicit TradingSignalGeneratorUi(QWidget *parent = 0);
    ~TradingSignalGeneratorUi();

signals:
    void newRecordCreated(const Record &r);

public slots:
    void manualAddRecord();

private:
    Ui::TradingSignalGeneratorUi *ui;
};

#endif // TRADINGSIGNALGENERATORUI_H
