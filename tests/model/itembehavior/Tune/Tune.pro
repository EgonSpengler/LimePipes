#-------------------------------------------------
#
# Project created by QtCreator 2012-08-16T14:10:42
#
#-------------------------------------------------
include( ../../../tests.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/itembehavior/itembehavior.pri )

QT       += testlib

QT       -= gui

TARGET = bin/tst_tunetest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_tunetest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
