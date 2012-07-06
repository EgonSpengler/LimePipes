include( ../common.pri )
include(symbols/symbols.pri)

DEPENDPATH += . symbols
INCLUDEPATH += . symbols

SOURCES += \
    model.cpp \
    tune.cpp \
    symbol.cpp \
    score.cpp \
    pitch.cpp

HEADERS += \
    model.h \
    tune.h \
    symbol.h \
    model_itemtypes.h \
    score.h \
    pitch.h
