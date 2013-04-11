#-------------------------------------------------
#
# Project created by QtCreator 2013-04-09T11:45:11
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = qt5
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    main.cpp \
    record.cpp \
    tradingengine.cpp \
    tradingsignalgenerator.cpp \
    tradingsignalgui.cpp


HEADERS += \
    record.h \
    tradingsignalgenerator.h \
    tradingsignalgui.h

FORMS += \
    tradingsignalgui.ui
