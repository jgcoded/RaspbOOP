#-------------------------------------------------
#
# Project created by QtCreator 2014-11-07T22:41:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RobotStation
TEMPLATE = app


SOURCES += main.cpp\
        stationwindow.cpp \
    robotconnectdialog.cpp

HEADERS  += stationwindow.h \
    robotconnectdialog.h

FORMS    += stationwindow.ui \
    robotconnectdialog.ui
