QT += core gui widgets printsupport

CONFIG += c++11

TARGET = lab1
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    genalgsearchmaximum.cpp

HEADERS += \
    genalgsearchmaximum.h
FORMS += \
    form.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../LibQCustomPlot/release/ -lLibQCustomPlot
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../LibQCustomPlot/debug/ -lLibQCustomPlot
else:unix: LIBS += -L$$OUT_PWD/../LibQCustomPlot/ -lLibQCustomPlot

INCLUDEPATH += $$PWD/../LibQCustomPlot
DEPENDPATH += $$PWD/../LibQCustomPlot
