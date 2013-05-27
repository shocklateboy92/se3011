#-------------------------------------------------
#
# Project created by QtCreator 2013-05-27T16:33:26
#
#-------------------------------------------------

include(../strategy.pri)

QT       += widgets

TARGET = PairTradingStrategy
TEMPLATE = lib
CONFIG += plugin

DEFINES += PAIRTRADINGSTRATEGY_LIBRARY

SOURCES += pair-trading-strategy.cpp \
    pair-trading-widget.cpp

HEADERS += pair-trading-strategy.h\
        pairtradingstrategy_global.h \
    pair-trading-widget.h

FORMS += \
    pair-trading-widget.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../core/release/ -lcore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../core/debug/ -lcore
else:mac: LIBS += -F$$OUT_PWD/../../core/ -framework core
else:unix: LIBS += -L$$OUT_PWD/../../core/ -lcore

INCLUDEPATH += $$PWD/../../core
DEPENDPATH += $$PWD/../../core
