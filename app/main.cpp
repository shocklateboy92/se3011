#include "main-window.h"
#include <QApplication>

#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QIcon::setThemeName("oxygen");

    MainWindow window;
    window.show();

    return app.exec();
}
