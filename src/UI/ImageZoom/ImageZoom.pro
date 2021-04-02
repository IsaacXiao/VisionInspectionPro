#-------------------------------------------------
#
# Project created by QtCreator 2015-07-29T10:59:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += release
CONFIG -= debug

TARGET = ImageZoom
TEMPLATE = app

SOURCES += \
    main.cpp\
    pixitem.cpp \
    mainwidget.cpp

HEADERS  += \
    pixitem.h \
    mainwidget.h

FORMS    += \
    mainwidget.ui

RESOURCES += \
    res.qrc
