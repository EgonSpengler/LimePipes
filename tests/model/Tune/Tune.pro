#-------------------------------------------------
#
# Project created by QtCreator 2012-08-16T14:10:42
#
#-------------------------------------------------
include( ../../tests.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/model.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/symbols/symbols.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/interfaces/interfaces.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/plugins/GreatHighlandBagpipe/GreatHighlandBagpipe.pri )

QT       += testlib

TARGET = bin/tst_tunetest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_tunetest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
