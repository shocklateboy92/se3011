#ifndef TRADINGFILESWIDGET_H
#define TRADINGFILESWIDGET_H

#include "trading-files-model.h"

#include <QDockWidget>
#include <QTableView>

namespace Ui {
class TradingFilesWidget;
}

class TradingFilesWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit TradingFilesWidget(TradingFilesModel *m_model, QWidget *parent = 0);
    ~TradingFilesWidget();

protected:
    void dropEvent(QDropEvent *e);
    void dragEnterEvent(QDragEnterEvent *e);

private slots:
    void onSelectionChanged();
    void onRemovebuttonClicked();

    void onAddbuttonClicked();

private:
    TradingFilesModel *m_model;
    Ui::TradingFilesWidget *ui;
};

#endif // TRADINGFILESWIDGET_H
