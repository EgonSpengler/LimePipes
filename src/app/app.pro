include( ../../LimePipes.pri )
include( ../model/model.pri )
include( ../model/datatypes/datatypes.pri )
include( ../model/symbols/symbols.pri )

TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    newtunedialog.cpp \
    addsymbolsdialog.cpp

HEADERS += \
    mainwindow.h \
    newtunedialog.h \
    addsymbolsdialog.h

RESOURCES += \
    app_resources.qrc

FORMS += \
    mainwindow.ui \
    newtunedialog.ui \
    addsymbolsdialog.ui

LIBS =  -L$${LIMEPIPES_SOURCE_TREE}/plugins_static -llp_greathighlandbagpipe

TARGET = ../../build/limepipes
