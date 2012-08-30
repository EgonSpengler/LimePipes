#-------------------------------------------------
#
# Project created by QtCreator 2012-08-30T09:35:57
#
#-------------------------------------------------
include( ../../tests.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/model.pri )

QT       += testlib

QT       -= gui

TARGET = bin/tst_rootitemtest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_rootitemtest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
