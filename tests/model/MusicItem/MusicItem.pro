#-------------------------------------------------
#
# Project created by QtCreator 2012-08-16T11:52:53
#
#-------------------------------------------------
include( ../../tests.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/model.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/datatypes/datatypes.pri )

QT       += testlib

QT       -= gui

TARGET = bin/tst_musicitemtest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_musicitemtest.cpp \
    testmusicitem.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    testmusicitem.h
