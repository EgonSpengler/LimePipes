#-------------------------------------------------
#
# Project created by QtCreator 2012-09-27T16:01:06
#
#-------------------------------------------------
include( ../../../tests.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/datatypes/datatypes.pri )

QT       += testlib

TARGET = bin/tst_pitchcontexttest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_pitchcontexttest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
