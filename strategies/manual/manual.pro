#-------------------------------------------------
#
# Project created by QtCreator 2013-05-27T18:16:55
#
#-------------------------------------------------

QT       += widgets

TARGET = manual
TEMPLATE = lib

DEFINES += MANUAL_LIBRARY

SOURCES += manual-strategy.cpp

HEADERS += manual-strategy.h\
        manual_global.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../core/release/ -lcore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../core/debug/ -lcore
else:unix: LIBS += -L$$OUT_PWD/../../core/ -lcore

INCLUDEPATH += $$PWD/../../core
DEPENDPATH += $$PWD/../../core
