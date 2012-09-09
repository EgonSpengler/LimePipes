include( ../../LimePipes.pri )
include( ../model/model.pri )
include( ../model/datatypes/datatypes.pri )
include( ../model/symbols/symbols.pri )

TEMPLATE = app

SOURCES += main.cpp \
    mainwindow.cpp \
    newtunedialog.cpp \
    addsymbolsdialog.cpp

RESOURCES += \
    app_resources.qrc

HEADERS += \
    mainwindow.h \
    newtunedialog.h \
    addsymbolsdialog.h

FORMS += \
    mainwindow.ui \
    newtunedialog.ui \
    addsymbolsdialog.ui

LIBS =  -L$${LIMEPIPES_SOURCE_TREE}/plugins_static -llp_greathighlandbagpipe

TARGET = ../../build/limepipes
