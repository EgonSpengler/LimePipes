#-------------------------------------------------
#
# Project created by QtCreator 2012-09-14T10:56:59
#
#-------------------------------------------------
include( ../../tests.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/model.pri )

QT       += testlib

QT       -= gui

TARGET = bin/tst_datapolicytest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_datapolicytest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
