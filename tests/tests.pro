#-------------------------------------------------
#
# Project created by QtCreator 2013-05-12T12:17:42
#
#-------------------------------------------------

QT       += widgets testlib

TARGET = tst_record-parsing-tests
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += c++11

TEMPLATE = app

SOURCES += tst_record-parsing-tests.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../core/release/ -lcore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../core/debug/ -lcore
else:mac: LIBS += -F$$OUT_PWD/../core/ -framework core
else:unix: LIBS += -L$$OUT_PWD/../core/ -lcore

INCLUDEPATH += $$PWD/../core
DEPENDPATH += $$PWD/../core
