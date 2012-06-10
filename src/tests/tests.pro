#-------------------------------------------------
#
# Project created by QtCreator 2012-04-22T12:14:09
#
#-------------------------------------------------

QT       += core testlib

TARGET = test_all
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += "../src"
DEPENDPATH += "../src"

SOURCES += main.cpp \
    model/modeltest.cpp \
    ../src/model/model.cpp \
    ../src/model/tune.cpp \
    ../src/model/symbol.cpp \
    bar/bartest.cpp \
    ../src/model/bar.cpp \
    tune/tunetest.cpp \
    symbol/symboltest.cpp \
    ../src/model/melodynote.cpp \
    melody_note/melodynotetest.cpp \
    score/scoretest.cpp \
    ../src/model/score.cpp \
    ../src/model/pitch.cpp


HEADERS += \
    autotest.h \
    model/modeltest.h \
    ../src/model/model.h \
    ../src/model/tune.h \
    ../src/model/symbol.h \
    bar/bartest.h \
    ../src/model/bar.h \
    tune/tunetest.h \
    symbol/symboltest.h \
    ../src/model/melodynote.h \
    melody_note/melodynotetest.h \
    score/scoretest.h \
    ../src/model/score.h \
    ../src/model/pitch.h
