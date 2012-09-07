include( $$LIMEPIPES_SOURCE_TREE/src/model/datatypes/datatypes.pri )
INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/greathighlandbagpipe.h \
    $$PWD/ghb_instrument.h \
    $$PWD/ghb_symboltypes.h \
    $$PWD/ghb_melodynote.h \
    $$PWD/ghb_doubling.h

SOURCES += \
    $$PWD/greathighlandbagpipe.cpp \
    $$PWD/ghb_instrument.cpp \
    $$PWD/ghb_melodynote.cpp \
    $$PWD/ghb_doubling.cpp
