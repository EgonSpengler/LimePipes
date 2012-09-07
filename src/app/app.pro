include( ../../LimePipes.pri )
include( ../model/model.pri )
include( ../model/datatypes/datatypes.pri )
include( ../model/symbols/symbols.pri )

TEMPLATE = app

SOURCES += main.cpp \
    mainwindow.cpp

RESOURCES += \
    app_resources.qrc

HEADERS += \
    mainwindow.h \

FORMS += \
    mainwindow.ui

LIBS =  -L$${LIMEPIPES_SOURCE_TREE}/plugins_static -llp_greathighlandbagpipe

TARGET = ../../build/limepipes
