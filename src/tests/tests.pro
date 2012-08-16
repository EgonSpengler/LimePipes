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
    musicmodel/musicmodeltest.cpp \
    bar/bartest.cpp \
    tune/tunetest.cpp \
    symbol/symboltest.cpp \
    melody_note/melodynotetest.cpp \
    score/scoretest.cpp \
    pitch/pitchtest.cpp \
    length/lengthtest.cpp \
    musicmodel/qt_modeltest/modeltest.cpp \
    musicitem/musicitemtest.cpp

HEADERS += \
    autotest.h \
    musicmodel/musicmodeltest.h \
    bar/bartest.h \
    tune/tunetest.h \
    symbol/symboltest.h \
    melody_note/melodynotetest.h \
    score/scoretest.h \
    pitch/pitchtest.h \
    length/lengthtest.h \
    musicmodel/qt_modeltest/modeltest.h \
    musicitem/musicitemtest.h
