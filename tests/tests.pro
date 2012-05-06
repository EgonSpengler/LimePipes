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
    sheetmusic/sheetmusictest.cpp \
    ../src/model/sheetmusic.cpp \
    ../src/model/tune.cpp \
    ../src/model/symbol.cpp \
    part/parttest.cpp \
    ../src/model/part.cpp \
    bar/bartest.cpp \
    ../src/model/bar.cpp \
    tune/tunetest.cpp \
    symbol/symboltest.cpp


HEADERS += \
    autotest.h \
    model/modeltest.h \
    ../src/model/model.h \
    sheetmusic/sheetmusictest.h \
    ../src/model/sheetmusic.h \
    ../src/model/tune.h \
    ../src/model/symbol.h \
    part/parttest.h \
    ../src/model/part.h \
    bar/bartest.h \
    ../src/model/bar.h \
    tune/tunetest.h \
    symbol/symboltest.h
