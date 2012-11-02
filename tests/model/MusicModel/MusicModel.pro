#-------------------------------------------------
#
# Project created by QtCreator 2012-08-16T11:53:18
#
#-------------------------------------------------
include( ../../tests.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/model.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/datatypes/datatypes.pri )

QT       += testlib

TARGET = bin/tst_musicmodeltest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += tst_musicmodeltest.cpp \
    qt_modeltest/modeltest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    qt_modeltest/modeltest.h

LIBS =  -L$${TEST_PLUGINS_FOLDER} -llp_musicmodeltestplugin

