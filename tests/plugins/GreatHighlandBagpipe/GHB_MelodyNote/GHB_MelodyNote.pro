#-------------------------------------------------
#
# Project created by QtCreator 2012-09-07T12:13:47
#
#-------------------------------------------------
include( ../../../tests.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/model.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/symbols/symbols.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/plugins/GreatHighlandBagpipe/GreatHighlandBagpipe.pri )

QT       += testlib

QT       -= gui

TARGET = bin/tst_ghb_melodynotetest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_ghb_melodynotetest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
