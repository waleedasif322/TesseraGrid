#-------------------------------------------------
#
# Project created by QtCreator 2013-09-26T15:55:50
#
#-------------------------------------------------

QT       += core
QT       += widgets

QT       -= gui

TARGET = Project1_6
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    MainWindow.cpp \
    ControlPanel.cpp \
    TesseraParameters.cpp \
    ImageWindow.cpp \
    tileconverter.cpp \
    HSL.cpp

HEADERS += \
    MainWindow.h \
    ControlPanel.h \
    TesseraParameters.h \
    ImageWindow.h \
    Globals.h \
    tileconverter.h \
    HSL.h

RESOURCES += \
    application.qrc
