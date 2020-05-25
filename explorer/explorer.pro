QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = explorer
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        datamodel.cpp

HEADERS += \
        mainwindow.h \
        datamodel.h

FORMS += \
        mainwindow.ui
