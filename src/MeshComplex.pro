#-------------------------------------------------
#
# Project created by QtCreator 2016-03-28T07:48:55
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS += "-std=c++11"

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MeshComplex
TEMPLATE = app


SOURCES += main.cpp\
    meshscene.cpp \
        mainwindow.cpp \
    meshview.cpp \
    cmapplication.cpp

HEADERS  += mainwindow.h \
    meshscene.h \
    meshview.h \
    cmapplication.h

FORMS    += mainwindow.ui
