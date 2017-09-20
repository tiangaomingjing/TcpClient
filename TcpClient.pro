#-------------------------------------------------
#
# Project created by QtCreator 2017-09-18T21:15:00
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TcpClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    pduitemwidget.cpp

HEADERS  += mainwindow.h \
    pduitemwidget.h

FORMS    += mainwindow.ui \
    pduitemwidget.ui

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    resource.qrc

