#-------------------------------------------------
#
# Project created by QtCreator 2012-09-12T17:18:39
#
#-------------------------------------------------
include( ../../tests.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/datatypes/datatypes.pri )

QT       += testlib

TARGET = bin/tst_newtunedialogtest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_newtunedialogtest.cpp \
    ../../../src/app/newtunedialog.cpp

HEADERS += \
    ../../../src/app/newtunedialog.h

FORMS += \
    ../../../src/app/newtunedialog.ui

DEFINES += SRCDIR=\\\"$$PWD/\\\"
