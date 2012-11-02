include( ../LimePipes.pri )

isEmpty(TEMPLATE):TEMPLATE=app
CONFIG += qt warn_on console depend_includepath testcase qtestlib
CONFIG -= app_bundle

TEST_PLUGINS_FOLDER = $$PWD/plugins_bin

UI_DIR = $$PWD/uics
MOC_DIR = $$PWD/mocs
OBJECTS_DIR = $$PWD/objs
RCC_DIR = $$PWD/rccs
