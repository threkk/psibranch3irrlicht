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
        mainwindow.cpp\
        ..\..\source\Irrlicht\ParticleModel.cpp

HEADERS  += mainwindow.h\
        ..\..\include\ParticleModel.h

FORMS    += mainwindow.ui

INCLUDEPATH += ..\..\include
LIBS += -L..\..\bin\Win32-VisualStudio -lIrrlicht
