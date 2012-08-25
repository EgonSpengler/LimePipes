#-------------------------------------------------
#
# Project created by QtCreator 2012-08-24T12:45:04
#
#-------------------------------------------------
include( ../tests.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/datatypes/datatypes.pri )

QT       += testlib

QT       -= gui

TARGET = bin/tst_timesignaturetest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += tst_timesignaturetest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
