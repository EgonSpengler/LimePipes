#-------------------------------------------------
#
# Project created by QtCreator 2012-10-20T14:54:21
#
#-------------------------------------------------
include( ../../tests.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/model.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/datatypes/datatypes.pri )

QT       += testlib

TARGET = bin/tst_symbolgraphicbuildertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_symbolgraphicbuildertest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
