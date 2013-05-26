#-------------------------------------------------
#
# Project created by QtCreator 2013-04-09T11:45:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = core
CONFIG   += console gui
CONFIG   += lib_bundle
CONFIG   += thread
CONFIG   += c++11

TEMPLATE = lib

CONFIG (release, debug|release) {
    DEFINES += QT_NO_DEBUG_OUTPUT
}

QMAKE_CXXFLAGS += -Wno-attributes

DEFINES += GROUP8_CORE_LIBRARY

SOURCES += \
    record.cpp \
    trading-engine.cpp \
    trading-evaluator.cpp \
    trading-file-reader.cpp \
    trading-files-model.cpp \
    records-model.cpp \
    trading-signal-generator.cpp \
    order.cpp \
    trading-strategy.cpp


HEADERS += \
    record.h \
    trading-engine.h \
    trading-evaluator.h \
    trading-file-reader.h \
    trading-files-model.h \
    records-model.h \
    trading-signal-generator.h \
    order.h \
    common.h \
    trading-strategy.h

