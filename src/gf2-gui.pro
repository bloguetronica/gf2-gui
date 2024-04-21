#-------------------------------------------------
#
# Project created by QtCreator 2018-03-04T20:31:13
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Added to provide backwards compatibility (C++11 support)
greaterThan(QT_MAJOR_VERSION, 4) {
    CONFIG += c++11
} else {
    QMAKE_CXXFLAGS += -std=c++11
}

TARGET = gf2-gui
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp\
    mainwindow.cpp \
    serial.cpp \
    about.cpp

HEADERS += \
    mainwindow.h \
    serial.h \
    about.h

FORMS += \
    mainwindow.ui \
    about.ui \
    serial.ui

RESOURCES += \
    resources.qrc

# Added installation option
unix {
    isEmpty(PREFIX) {
        PREFIX = /usr/local
    }
    target.path = $$PREFIX/bin
    icon.files += icons/gf2-gui.png
    icon.path = $$PREFIX/share/icons/hicolor/128x128/apps
    shortcut.files = misc/gf2-gui.desktop
    shortcut.path = $$PREFIX/share/applications
    INSTALLS += icon
    INSTALLS += shortcut
}

!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    icons/gf2-gui.png \
    misc/gf2-gui.desktop
