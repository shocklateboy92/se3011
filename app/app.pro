
QT += core gui widgets

TARGET  = seng
CONFIG += gui
CONFIG += app_bundle

CONFIG += c++11

TEMPLATE = app

SOURCES += \
    main.cpp \
    main-window.cpp \
    trading-files-widget.cpp \
    trading-signal-widget.cpp \
    trading-signal-results-widget.cpp \
    trading-evaluator-widget.cpp \
    trading-signal-group-08.cpp \
    qcustomplot.cpp \
    trading-evaluator-graph.cpp \
    overlay.cpp


HEADERS += \
    main-window.h \
    trading-files-widget.h \
    trading-signal-widget.h \
    trading-signal-results-widget.h \
    trading-evaluator-widget.h \
    trading-signal-group-08.h \
    qcustomplot.h \
    trading-evaluator-graph.h \
    overlay.h

FORMS += \
    main-window.ui \
    trading-files-widget.ui \
    trading-signal-results-widget.ui \
    trading-signal-widget.ui \
    trading-evaluator-widget.ui \
    trading-signal-group-08.ui \
    trading-evaluator-graph.ui \
    overlay.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../core/release/ -lcore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../core/debug/ -lcore
else:mac: LIBS += -F$$OUT_PWD/../core/ -framework core
else:unix: LIBS += -L$$OUT_PWD/../core/ -lcore

INCLUDEPATH += $$PWD/../core
DEPENDPATH += $$PWD/../core
QT += printsupport
