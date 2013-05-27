#-------------------------------------------------
#
# Project created by QtCreator 2013-05-27T15:05:20
#
#-------------------------------------------------

include (../strategy.pri)

QT       += widgets

TARGET = group8-strategy
TEMPLATE = lib

DEFINES += GROUP8STRATEGY_LIBRARY

SOURCES += group8-strategy.cpp \
        trading-signal-group-08.cpp

HEADERS += group8-strategy.h \
        group8-strategy_global.h \
        trading-signal-group-08.h

FORMS += trading-signal-group-08.ui
