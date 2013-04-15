#ifndef TRADINGFILESWIDGET_H
#define TRADINGFILESWIDGET_H

#include "trading-files-model.h"

#include <QDockWidget>

namespace Ui {
class TradingFilesWidget;
}

class TradingFilesWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit TradingFilesWidget(TradingFilesModel *model, QWidget *parent = 0);
    ~TradingFilesWidget();

private:
    TradingFilesModel *model;
    Ui::TradingFilesWidget *ui;
};

#endif // TRADINGFILESWIDGET_H
