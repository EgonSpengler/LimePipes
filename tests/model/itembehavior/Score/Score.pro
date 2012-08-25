#-------------------------------------------------
#
# Project created by QtCreator 2012-08-16T11:54:00
#
#-------------------------------------------------
include( ../../../tests.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/datatypes/datatypes.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/itembehavior/itembehavior.pri )

QT       += testlib

QT       -= gui

TARGET = bin/tst_scoretest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_scoretest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
