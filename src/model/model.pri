include( $$LIMEPIPES_SOURCE_TREE/src/model/musicfont/musicfont.pri )

INCLUDEPATH += $$PWD

SOURCES += \
    $$PWD/musicmodel.cpp \
    $$PWD/musicitem.cpp \
    $$PWD/tune.cpp \
    $$PWD/symbol.cpp \
    $$PWD/score.cpp \
    $$PWD/rootitem.cpp \
    $$PWD/symbolgraphicbuilder.cpp \
    $$PWD/instrumentmanager.cpp

HEADERS += \
    $$PWD/musicmodel.h \
    $$PWD/musicitem.h \
    $$PWD/itemdatatypes.h \
    $$PWD/tune.h \
    $$PWD/symbol.h \
    $$PWD/score.h \
    $$PWD/rootitem.h \
    $$PWD/../interfaces/interfaceglobals.h \
    $$PWD/musicmodelinterface.h \
    $$PWD/symbolgraphicbuilder.h \
    $$PWD/instrumentmanager.h \
    $$PWD/commands/insertitemcommand.h \
    $$PWD/commands/removeitemscommand.h
