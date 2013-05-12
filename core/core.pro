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
CONFIG   += thread

TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

CONFIG (release, debug|release) {
    DEFINES += QT_NO_DEBUG_OUTPUT
}

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
    trading-signal-results-widget.cpp \
    records-model.cpp \
    trading-evaluator-widget.cpp \
    trading-signal-momentum.cpp \
    order.cpp \
    trading-signal-group-08.cpp


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
    trading-signal-results-widget.h \
    records-model.h \
    trading-evaluator-widget.h \
    trading-signal-momentum.h \
    order.h \
    trading-signal-group-08.h

FORMS += \
    main-window.ui \
    trading-files-widget.ui \
    trading-signal-results-widget.ui \
    trading-signal-widget.ui \
    trading-evaluator-widget.ui \
    trading-signal-momentum.ui \
    trading-signal-group-08.ui
