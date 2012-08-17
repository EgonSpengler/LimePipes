#-------------------------------------------------
#
# Project created by QtCreator 2012-08-16T11:44:46
#
#-------------------------------------------------
include( ../tests.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/model.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/symbols/symbols.pri )

QT       += testlib

QT       -= gui

TARGET = tst_bartest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_bartest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
