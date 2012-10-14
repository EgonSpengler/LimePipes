#-------------------------------------------------
#
# Project created by QtCreator 2012-10-13T18:02:50
#
#-------------------------------------------------
include( ../../../tests.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/views/treeview/treeview.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/model.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/datatypes/datatypes.pri )

QT       += testlib

TARGET = bin/tst_musicproxymodeltest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_musicproxymodeltest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
