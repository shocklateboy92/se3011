#include "main-window.h"
#include <QApplication>

#include <QVariant>
#include <functional>
#include <QDebug>

template <typename T>
QVariant makeVariant(T t, QWidget *o) { //this part is legit - it calls method on object
    return QVariant((o->*t)());
}

QVariant mVar() {
    return QVariant();
}

QVariant mVar1(int v) {
    return QVariant(v);
}

QVariant mVar2(std::function<bool()> f) {
    return QVariant(f());
}

bool func() {
    return false;
}

QVariant mVar3(std::function<bool(const QWidget&)> f, QWidget *o) {
    return QVariant(f(*o));
}

template <typename Return>
QVariant mVar4(std::function<Return(const QWidget&)> f, QWidget *o) {
    return QVariant(f(*o));
}

template <typename Return, typename Object>
QVariant mVar5(std::function<Return(const Object&)> f, Object *o) {
    return QVariant(f(*o));
}

template <typename T>
std::function<QVariant(Record *r)>
O_(std::function<T(const Record&)> f) {
    return std::bind(&mVar5<T, Record>, f, std::placeholders::_1);
}

QList<std::function<QVariant(Record *r)>> fields = {
        O_<bool>(&Record::isValid),
        O_<QString>(&Record::instrument),
        O_<QDate>(&Record::date),
        O_<QTime>(&Record::time),
        O_<double>(&Record::price),
        O_<qint64>(&Record::bidId)
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.show();
    int i;
    std::function<QVariant()> f = mVar;
    auto b = std::bind(&mVar1, i);
//    f = b;

    QVariant vt = mVar3(&MainWindow::acceptDrops, &window);
    vt          = mVar4<bool>(&MainWindow::acceptDrops, &window);

    QList<std::function<QVariant()>> l = {
            f,
            b,
            std::bind(&mVar2, func),
            std::bind(&mVar3, &MainWindow::acceptDrops, &window),
            std::bind(&mVar4<bool>, &MainWindow::acceptDrops, &window),
            std::bind(&mVar4<QString>, &MainWindow::objectName, &window),
            std::bind(&mVar5<QString, MainWindow>, &MainWindow::objectName, &window)
    };

    l.append(std::bind(&mVar5<QString, QVariant>, &QVariant::toString, &vt));

    std::function<QVariant(MainWindow*)> kl =
            std::bind(&mVar4<QString>, &MainWindow::objectName, std::placeholders::_1);


    for (auto v : l) {
        qDebug() << v();
    }

    window.setAcceptDrops(true);
    qDebug() << l[3]();
    qDebug() << kl(&window);


    Record r;
    for (auto &field : fields) {
        qDebug() << field(&r);
    }

//    QVariant v1 = b();

    return app.exec();
}
