include( ../common.pri )
include(../model/model.pro)

TEMPLATE = app
INCLUDEPATH += ../model/ ../model/symbols/
DEPENDPATH += ../model/ ../model/symbols/

QT       += core testlib

TARGET = ../test_all
CONFIG   += console
CONFIG   -= app_bundle

SOURCES += main.cpp \
    model/modeltest.cpp \
    bar/bartest.cpp \
    tune/tunetest.cpp \
    symbol/symboltest.cpp \
    melody_note/melodynotetest.cpp \
    score/scoretest.cpp

HEADERS += \
    autotest.h \
    model/modeltest.h \
    bar/bartest.h \
    tune/tunetest.h \
    symbol/symboltest.h \
    melody_note/melodynotetest.h \
    score/scoretest.h \
