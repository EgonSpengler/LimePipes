#-------------------------------------------------
#
# Project created by QtCreator 2012-09-07T11:39:00
#
#-------------------------------------------------
include( ../../../tests.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/model.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/symbols/symbols.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/datatypes/datatypes.pri )

QT       += testlib

TARGET = bin/tst_melodynotetest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_melodynotetest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
