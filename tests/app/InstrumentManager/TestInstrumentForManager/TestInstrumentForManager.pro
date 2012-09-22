#-------------------------------------------------
#
# Project created by QtCreator 2012-09-21T18:00:27
#
#-------------------------------------------------
include( ../../../tests.pri )
include( ../InstrumentManager/InstrumentManager.pri )
include( ../../../../src/model/datatypes/datatypes.pri )

TEMPLATE      = lib
CONFIG       += plugin
TARGET        = lp_testinstrument
DESTDIR       = $$INSTRUMENT_MANAGER_PLUGIN_DIR

HEADERS += \
    testinstrumentformanager.h

SOURCES += \
    testinstrumentformanager.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

UI_DIR = $$PWD/uics
MOC_DIR = $$PWD/mocs
OBJECTS_DIR = $$PWD/objs
RCC_DIR = $$PWD/rccs
