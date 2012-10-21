#-------------------------------------------------
#
# Project created by QtCreator 2012-08-27T11:29:38
#
#-------------------------------------------------
include( ../../../tests.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/interfaces/interfaces.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/datatypes/datatypes.pri )

QT       += testlib

TARGET = bin/tst_instrumenttest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_instrumenttest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

