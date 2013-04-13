#-------------------------------------------------
#
# Project created by QtCreator 2013-04-09T11:45:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt5
CONFIG   += console gui
CONFIG   += app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
    main.cpp \
    record.cpp \
    tradingengine.cpp \
    tradingsignalgenerator.cpp \
    mainwindow.cpp \
    tradingsignalgeneratorui.cpp


HEADERS += \
    record.h \
    tradingengine.h \
    tradingsignalgenerator.h \
    mainwindow.h \
    tradingsignalgeneratorui.h

FORMS += \
    mainwindow.ui \
    tradingsignalgeneratorui.ui
