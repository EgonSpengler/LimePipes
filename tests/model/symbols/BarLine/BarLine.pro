#-------------------------------------------------
#
# Project created by QtCreator 2012-09-07T11:41:52
#
#-------------------------------------------------
include( ../../../tests.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/model.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/datatypes/datatypes.pri )

QT       += testlib

TARGET = bin/tst_barlinetest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    tst_barlinetest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
