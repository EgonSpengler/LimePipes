#-------------------------------------------------
#
# Project created by QtCreator 2012-09-22T10:35:07
#
#-------------------------------------------------
include( ../../tests.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/model.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/datatypes/datatypes.pri )

QT       += testlib

TARGET = bin/tst_mainwindowtest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

LIBS =  -L$${LIMEPIPES_SOURCE_TREE}/plugins_static -llp_greathighlandbagpipe

SOURCES += tst_mainwindowtest.cpp \
    ../../../src/app/newtunedialog.cpp \
    ../../../src/app/mainwindow.cpp \
    ../../../src/app/addsymbolsdialog.cpp \
    ../../../src/app/instrumentmanager.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../../src/app/newtunedialog.h \
    ../../../src/app/mainwindow.h \
    ../../../src/app/addsymbolsdialog.h \
    ../../../src/app/instrumentmanager.h

FORMS += \
    ../../../src/app/newtunedialog.ui \
    ../../../src/app/mainwindow.ui \
    ../../../src/app/addsymbolsdialog.ui

RESOURCES += \
    ../../../src/app/app_resources.qrc
