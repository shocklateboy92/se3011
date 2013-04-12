#-------------------------------------------------
#
# Project created by QtCreator 2013-04-09T11:45:11
#
#-------------------------------------------------

QT       += core gui

TARGET = qt5
CONFIG   += console gui
CONFIG   += app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
    main.cpp \
    record.cpp \
    tradingengine.cpp \
    tradingsignalgenerator.cpp


HEADERS += \
    record.h \
    tradingsignalgenerator.h

FORMS += \
    tradingsignalgui.ui
