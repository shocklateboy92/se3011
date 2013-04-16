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
QMAKE_CXX = g++-4.8
QMAKE_CC = gcc-4.8
QMAKE_LINK = g++-4.8


SOURCES += \
    main.cpp \
    record.cpp \
    main-window.cpp \
    trading-engine.cpp \
    trading-evaluator.cpp \
    trading-signal-generator.cpp \
    trading-file-reader.cpp \
    trading-files-model.cpp \
    trading-files-widget.cpp \
    trading-signal-widget.cpp \
    trading-signal-results-widget.cpp


HEADERS += \
    record.h \
    main-window.h \
    trading-engine.h \
    trading-evaluator.h \
    trading-signal-generator.h \
    trading-file-reader.h \
    trading-files-model.h \
    trading-files-widget.h \
    trading-signal-widget.h \
    trading-signal-results-widget.h

FORMS += \
    main-window.ui \
    trading-files-widget.ui \
    trading-signal-results-widget.ui \
    trading-signal-widget.ui
