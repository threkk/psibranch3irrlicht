#-------------------------------------------------
#
# Project created by QtCreator 2014-03-18T11:40:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    ParticleModel.cpp \
    XML.cpp \
    Util.cpp

HEADERS  += mainwindow.h \
    ParticleModel.h \
    XML.h \
    Util.h

FORMS    += mainwindow.ui

INCLUDEPATH += ..\..\include
LIBS += -L..\..\lib\Win32-visualstudio -lIrrlicht

OTHER_FILES +=

