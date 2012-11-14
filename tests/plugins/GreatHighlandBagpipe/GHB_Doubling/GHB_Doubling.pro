#-------------------------------------------------
#
# Project created by QtCreator 2012-09-07T12:29:35
#
#-------------------------------------------------
include( ../../../tests.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/model.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/interfaces/interfaces.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/plugins/GreatHighlandBagpipe/GreatHighlandBagpipe.pri )

QT       += testlib

TARGET = bin/tst_ghb_doublingtest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_ghb_doublingtest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
