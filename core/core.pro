QT       -= gui

TARGET = adsbData-core
CONFIG   += c++11
DEFINES += CORE_LIBRARY
TEMPLATE = lib

QMAKE_CXXFLAGS += -fvisibility=hidden -fvisibility-inlines-hidden
QMAKE_LFLAGS += -fvisibility=hidden -fvisibility-inlines-hidden

SOURCES += \
    aircraft.cpp \
    position.cpp

HEADERS += \
    aircraft.h \
    position.h \
    core_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
