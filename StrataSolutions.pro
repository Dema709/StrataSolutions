#
#  QCustomPlot Plot Examples
#

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): CONFIG += c++11
lessThan(QT_MAJOR_VERSION, 5): QMAKE_CXXFLAGS += -std=c++11

TARGET = StrataSolutions
TEMPLATE = app

SOURCES += main.cpp \
    GraphWidget.cpp \
    QCustomPlot/qcustomplot.cpp \
    WorkerThread.cpp

HEADERS  += \
    GraphWidget.h \
    QCustomPlot/qcustomplot.h \
    WorkerThread.h
