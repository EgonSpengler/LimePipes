include( ../../LimePipes.pri )
include( ../model/model.pri )
include( ../model/datatypes/datatypes.pri )
include( ../model/symbols/symbols.pri )
include( ../views/treeview/treeview.pri )

TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    newtunedialog.cpp \
    addsymbolsdialog.cpp \
    instrumentmanager.cpp

HEADERS += \
    mainwindow.h \
    newtunedialog.h \
    addsymbolsdialog.h \
    instrumentmanager.h

RESOURCES += \
    app_resources.qrc

FORMS += \
    mainwindow.ui \
    newtunedialog.ui \
    addsymbolsdialog.ui

LIBS =  -L$${LIMEPIPES_SOURCE_TREE}/plugins_static -llp_greathighlandbagpipe

TARGET = ../../build/limepipes
