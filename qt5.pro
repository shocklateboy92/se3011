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
    main-window.cpp \
    trading-engine.cpp \
    trading-evaluator.cpp \
    trading-signal-generator.cpp \
    trading-signal-generatorui.cpp \
    trading-file-reader.cpp


HEADERS += \
    record.h \
    main-window.h \
    trading-engine.h \
    trading-evaluator.h \
    trading-signal-generator.h \
    trading-signal-generator-ui.h \
    trading-file-reader.h

FORMS += \
    main-window.ui \
    trading-signal-generator-ui.ui
