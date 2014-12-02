#-------------------------------------------------
#
# Project created by QtCreator 2014-12-01T20:49:39
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = adsbData
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    reader.cpp \
    aircraft.cpp \
    position.cpp

HEADERS += \
    reader.h \
    aircraft.h \
    position.h
