#include "tradingsignalgui.h"
#include "ui_tradingsignalgui.h"

TradingSignalGUI::TradingSignalGUI(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::TradingSignalGUI)
{
    ui->setupUi(this);
}

TradingSignalGUI::~TradingSignalGUI()
{
    delete ui;
}

void TradingSignalGUI::on_pushButton_3_clicked()
{
    QString path = QFileDialog::getExistingDirectory (this, tr("Directory"), directory.path());
    if ( path.isNull() == false )
    {
        directory.setPath(path);
    }
}
