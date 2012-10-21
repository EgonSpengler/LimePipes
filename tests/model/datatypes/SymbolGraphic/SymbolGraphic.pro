#-------------------------------------------------
#
# Project created by QtCreator 2012-10-20T09:42:34
#
#-------------------------------------------------
include( ../../../tests.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/datatypes/datatypes.pri )

QT       += testlib

TARGET = bin/tst_symbolgraphictest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_symbolgraphictest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
