#-------------------------------------------------
#
# Project created by QtCreator 2012-10-02T19:15:27
#
#-------------------------------------------------
include( ../../../tests.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/views/treeview/treeview.pri )

QT       += testlib

TARGET = bin/tst_treeviewtest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_treeviewtest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
