#-------------------------------------------------
#
# Project created by QtCreator 2012-08-29T07:39:00
#
#-------------------------------------------------
include( ../../tests.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/interfaces/interfaces.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/plugins/GreatHighlandBagpipe/GreatHighlandBagpipe.pri )

QT       += testlib

QT       -= gui

TARGET = tst_greathighlandbagpipetest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += tst_greathighlandbagpipetest.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

