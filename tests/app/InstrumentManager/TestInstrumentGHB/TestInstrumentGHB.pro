#-------------------------------------------------
#
# Project created by QtCreator 2012-09-21T09:26:21
#
#-------------------------------------------------
include( ../../../tests.pri )
include( ../InstrumentManager/InstrumentManager.pri )
include( ../../../../src/model/datatypes/datatypes.pri )


TEMPLATE      = lib
CONFIG       += plugin
TARGET        = lp_testinstrumentGHB
DESTDIR       = $$INSTRUMENT_MANAGER_PLUGIN_DIR

HEADERS += \
    testinstrumentghb.h

SOURCES += \
    testinstrumentghb.cpp

UI_DIR = $$PWD/uics
MOC_DIR = $$PWD/mocs
OBJECTS_DIR = $$PWD/objs
RCC_DIR = $$PWD/rccs

