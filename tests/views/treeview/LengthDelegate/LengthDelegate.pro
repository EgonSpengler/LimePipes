#-------------------------------------------------
#
# Project created by QtCreator 2012-10-07T09:58:50
#
#-------------------------------------------------
include( ../../../tests.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/views/treeview/treeview.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/model.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/datatypes/datatypes.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/symbols/symbols.pri )

QT       += testlib

TARGET = bin/tst_lengthdelegatetest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_lengthdelegatetest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
