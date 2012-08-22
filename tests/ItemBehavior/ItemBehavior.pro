#-------------------------------------------------
#
# Project created by QtCreator 2012-08-22T10:12:10
#
#-------------------------------------------------
include( ../tests.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/model.pri )

QT       += testlib

QT       -= gui

TARGET = bin/tst_itembehaviortest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_itembehaviortest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
