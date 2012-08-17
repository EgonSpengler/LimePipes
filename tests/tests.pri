include( ../LimePipes.pri )

isEmpty(TEMPLATE):TEMPLATE=app
CONFIG += qt warn_on console depend_includepath testcase qtestlib
CONFIG -= app_bundle
