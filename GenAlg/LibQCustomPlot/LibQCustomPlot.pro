QT       += gui

TARGET = LibQCustomPlot
TEMPLATE = lib

DEFINES += QCP_LIB_DECL

SOURCES += qcustomplot.cpp

HEADERS += qcustomplot.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
