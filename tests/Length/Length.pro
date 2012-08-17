#-------------------------------------------------
#
# Project created by QtCreator 2012-08-16T11:48:43
#
#-------------------------------------------------
include( ../tests.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/model.pri )

QT       += testlib

QT       -= gui

TARGET = tst_lengthtest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_lengthtest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
