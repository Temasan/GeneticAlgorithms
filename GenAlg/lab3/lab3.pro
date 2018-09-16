#-------------------------------------------------
#
# Project created by QtCreator 2018-05-11T00:52:05
#
#-------------------------------------------------

QT       += core gui widgets printsupport

CONFIG += c++11


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab3
TEMPLATE = app

INCLUDEPATH = ../lab1

SOURCES += main.cpp\
        mainwindow.cpp \
    genalgsalesman.cpp

HEADERS  += mainwindow.h \
    genalgsalesman.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../LibQCustomPlot/release/ -lLibQCustomPlot
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../LibQCustomPlot/debug/ -lLibQCustomPlot
else:unix: LIBS += -L$$OUT_PWD/../LibQCustomPlot/ -lLibQCustomPlot

INCLUDEPATH += $$PWD/../LibQCustomPlot
DEPENDPATH += $$PWD/../LibQCustomPlot

RESOURCES += \
    data.qrc
