#-------------------------------------------------
#
# Project created by QtCreator 2012-10-27T18:09:16
#
#-------------------------------------------------
include( ../../../tests.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/musicfont/musicfont.pri )

QT       += testlib

TARGET = tst_musicfonttest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_musicfonttest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
