#-------------------------------------------------
#
# Project created by QtCreator 2012-08-16T13:45:58
#
#-------------------------------------------------
include( ../tests.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/model.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/symbols/symbols.pri )

QT       += testlib

QT       -= gui

TARGET = tst_melodynotetest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_melodynotetest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
