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
    $$LIMEPIPES_SOURCE_TREE/src/app/addsymbolsdialog.cpp

HEADERS += \
    $$LIMEPIPES_SOURCE_TREE/src/app/addsymbolsdialog.h

FORMS += \
    $$LIMEPIPES_SOURCE_TREE/src/app/addsymbolsdialog.ui

DEFINES += SRCDIR=\\\"$$PWD/\\\"
