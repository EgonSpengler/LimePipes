#-------------------------------------------------
#
# Project created by QtCreator 2012-09-14T10:11:37
#
#-------------------------------------------------
include( ../../tests.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/model.pri )

QT       += testlib

QT       -= gui

TARGET = bin/tst_dataruletest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_dataruletest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
