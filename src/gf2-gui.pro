#-------------------------------------------------
#
# Project created by QtCreator 2018-03-04T20:31:13
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gf2-gui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    serial.cpp \
    about.cpp

HEADERS  += mainwindow.h \
    serial.h \
    about.h

FORMS    += mainwindow.ui \
    about.ui \
    serial.ui

RESOURCES += \
    resources.qrc
