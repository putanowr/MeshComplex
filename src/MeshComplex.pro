#-------------------------------------------------
#
# Project created by QtCreator 2016-03-28T07:48:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MeshComplex
TEMPLATE = app


SOURCES += main.cpp\
    meshscene.cpp \
        mainwindow.cpp \
    meshview.cpp \
    cmapplication.cpp \
    meshcomplex.cpp \
    graphicsnode.cpp \
    graphiscedge.cpp \
    graphisccell.cpp

HEADERS  += mainwindow.h \
    meshscene.h \
    meshview.h \
    cmapplication.h \
    meshcomplex.h \
    graphicsnode.h \
    graphiscedge.h \
    zipper.h \
    graphicscell.h

FORMS    += mainwindow.ui

LP = $$(LD_LIBRARY_PATH)
LP = $$replace(LP, ":", " ")
for (var, $$list($$LP)) {
LIBS += -L$$var
}
message($$LIBS)
QMAKE_CXXFLAGS += "-std=c++11"

LIBS += -lMOAB
