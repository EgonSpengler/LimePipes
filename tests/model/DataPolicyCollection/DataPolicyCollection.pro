#-------------------------------------------------
#
# Project created by QtCreator 2012-09-14T13:40:12
#
#-------------------------------------------------
include( ../../tests.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/model.pri )

QT       += testlib

QT       -= gui

TARGET = bin/tst_datapolicycollectiontest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_datapolicycollectiontest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
