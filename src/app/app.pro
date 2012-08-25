include( ../../LimePipes.pri )
include( ../model/model.pri )
include( ../model/symbols/symbols.pri )
include( ../model/datatypes/datatypes.pri )

TEMPLATE = app

SOURCES += main.cpp \
    mainwindow.cpp

RESOURCES += \
    app_resources.qrc

HEADERS += \
    mainwindow.h \

FORMS += \
    mainwindow.ui

TARGET = bin/limepipes
