#-------------------------------------------------
#
# Project created by QtCreator 2012-09-20T17:43:40
#
#-------------------------------------------------
include( ../../../tests.pri )
include( InstrumentManager.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/model.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/datatypes/datatypes.pri )

!exists( $${LIMEPIPES_STATIC_PLUGINS_FOLDER}/liblp_greathighlandbagpipe.a ) {
    error( "No static plugin for great highland bagpipe in the folder $${LIMEPIPES_STATIC_PLUGINS_FOLDER} found. Open LimePipes.pro and build it first." )
}

QT       += testlib

TARGET = $$INSTRUMENT_MANAGER_BUILD_DIR/tst_instrumentmanagertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += tst_instrumentmanagertest.cpp \
    $$LIMEPIPES_SOURCE_TREE/src/app/instrumentmanager.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

LIBS =  -L$${LIMEPIPES_SOURCE_TREE}/plugins_static -llp_greathighlandbagpipe

HEADERS += \
    $$LIMEPIPES_SOURCE_TREE/src/app/instrumentmanager.h
