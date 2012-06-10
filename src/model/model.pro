include( ../common.pri )

DEPENDPATH += . symbols
INCLUDEPATH += . symbols

include(symbols/symbols.pri)

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
