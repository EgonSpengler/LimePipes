include( ../common.pri )
include(symbols/symbols.pri)

DEPENDPATH += . symbols
INCLUDEPATH += . symbols

SOURCES += \
    tune.cpp \
    symbol.cpp \
    score.cpp \
    pitch.cpp \
    musicmodel.cpp \
    ../model/musicitem.cpp \
    length.cpp

HEADERS += \
    tune.h \
    symbol.h \
    model_itemtypes.h \
    score.h \
    pitch.h \
    musicmodel.h \
    ../model/musicitem.h \
    length.h
