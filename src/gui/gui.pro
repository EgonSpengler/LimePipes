include( ../common.pri )
include(../model/model.pro)

TEMPLATE = app
INCLUDEPATH += ../model/ ../model/symbols/
DEPENDPATH += ../model/ ../model/symbols/

SOURCES += main.cpp \
    mainwindow.cpp

RESOURCES += \
    resources.qrc

HEADERS += \
    mainwindow.h \

FORMS += \
    mainwindow.ui

TARGET = ../limepipes
