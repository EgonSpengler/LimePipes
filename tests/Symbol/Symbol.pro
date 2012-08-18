#-------------------------------------------------
#
# Project created by QtCreator 2012-08-16T11:54:17
#
#-------------------------------------------------
include( ../tests.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/model.pri )

QT       += testlib

QT       -= gui

TARGET = bin/tst_symboltest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_symboltest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
