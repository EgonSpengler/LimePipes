#-------------------------------------------------
#
# Project created by QtCreator 2012-10-28T07:43:14
#
#-------------------------------------------------
include( ../../../tests.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/musicfont/musicfont.pri )

QT       += testlib

TARGET = bin/tst_emmentalermusicfonttest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_emmentalermusicfonttest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
