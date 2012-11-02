#-------------------------------------------------
#
# Project created by QtCreator 2012-11-01T16:39:51
#
#-------------------------------------------------
include( ../tests.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/interfaces/interfaces.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/datatypes/datatypes.pri )
include( $$LIMEPIPES_SOURCE_TREE/src/model/model.pri )

TEMPLATE      = lib
CONFIG       += plugin static
TARGET        = lp_musicmodeltestplugin
DESTDIR       = $$TEST_PLUGINS_FOLDER

SOURCES += musicmodeltestplugin.cpp \
    testinstrument.cpp

HEADERS += musicmodeltestplugin.h \
    testinstrument.h
