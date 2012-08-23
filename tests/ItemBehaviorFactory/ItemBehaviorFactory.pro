#-------------------------------------------------
#
# Project created by QtCreator 2012-08-22T13:18:09
#
#-------------------------------------------------
include( ../tests.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/model.pri )

QT       += testlib

QT       -= gui

TARGET = bin/tst_itembehaviorfactorytest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_itembehaviorfactorytest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
