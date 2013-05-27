#-------------------------------------------------
#
# Project created by QtCreator 2013-05-26T13:58:17
#
#-------------------------------------------------

include(../strategy.pri)

QT       += widgets

TARGET = momentum
TEMPLATE = lib
CONFIG += plugin

DEFINES += MOMENTUM_LIBRARY

SOURCES += momentum-strategy.cpp \
           trading-signal-momentum.cpp

HEADERS += \
    momentum-strategy.h \
    momentum_global.h \
    trading-signal-momentum.h

FORMS += trading-signal-momentum.ui

