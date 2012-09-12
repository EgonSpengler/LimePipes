#-------------------------------------------------
#
# Project created by QtCreator 2012-09-12T16:39:50
#
#-------------------------------------------------
include( ../../tests.pri )

QT       += testlib

TARGET = bin/tst_addsymbolsdialogtest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_addsymbolsdialogtest.cpp \
    ../../../src/app/addsymbolsdialog.cpp

HEADERS += \
    ../../../src/app/addsymbolsdialog.h

FORMS += \
    ../../../src/app/addsymbolsdialog.ui

DEFINES += SRCDIR=\\\"$$PWD/\\\"
