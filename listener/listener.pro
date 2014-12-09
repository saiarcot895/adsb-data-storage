QT += core network
QT -= gui

CONFIG += c++11
CONFIG -= app_bundle
TARGET = adsbData-listener
TEMPLATE = app

HEADERS += \
    reader.h

SOURCES += \
    main.cpp \
    reader.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../core/release/ -ladsbData-core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../core/debug/ -ladsbData-core
else:unix: LIBS += -L$$OUT_PWD/../core/ -ladsbData-core

INCLUDEPATH += $$PWD/../core
DEPENDPATH += $$PWD/../core
