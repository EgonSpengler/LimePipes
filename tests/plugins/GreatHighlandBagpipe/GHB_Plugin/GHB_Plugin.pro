#-------------------------------------------------
#
# Project created by QtCreator 2012-08-29T07:39:00
#
#-------------------------------------------------
include( ../../../tests.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/model.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/interfaces/interfaces.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/plugins/GreatHighlandBagpipe/GreatHighlandBagpipe.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/symbols/symbols.pri )

QT       += testlib

QT       -= gui

TARGET = bin/tst_ghb_plugintest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += tst_ghb_plugintest.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

