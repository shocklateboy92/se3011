#-------------------------------------------------
#
# Project created by QtCreator 2013-05-27T16:33:26
#
#-------------------------------------------------

QT       += widgets

TARGET = PairTradingStrategy
TEMPLATE = lib

DEFINES += PAIRTRADINGSTRATEGY_LIBRARY

SOURCES += pair-trading-strategy.cpp \
    pair-trading-widget.cpp

HEADERS += pair-trading-strategy.h\
        pairtradingstrategy_global.h \
    pair-trading-widget.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

FORMS += \
    pair-trading-widget.ui
