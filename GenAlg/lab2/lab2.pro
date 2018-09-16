#-------------------------------------------------
#
# Project created by QtCreator 2018-04-01T19:30:44
#
#-------------------------------------------------

QT       += core gui widgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab2
TEMPLATE = app


SOURCES += main.cpp\
    genalgrastrign.cpp

HEADERS  += genalgrastrign.h

FORMS    += widget.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../LibQCustomPlot/release/ -lLibQCustomPlot
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../LibQCustomPlot/debug/ -lLibQCustomPlot
else:unix: LIBS += -L$$OUT_PWD/../LibQCustomPlot/ -lLibQCustomPlot

INCLUDEPATH += $$PWD/../LibQCustomPlot
DEPENDPATH += $$PWD/../LibQCustomPlot
