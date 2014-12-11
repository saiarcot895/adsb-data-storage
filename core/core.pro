QT       -= gui

TARGET = adsbData-core
CONFIG   += c++11
DEFINES += CORE_LIBRARY
TEMPLATE = lib

QMAKE_CXXFLAGS += -fvisibility=hidden -fvisibility-inlines-hidden
QMAKE_LFLAGS += -fvisibility=hidden -fvisibility-inlines-hidden

SOURCES += \
    aircraft.cpp \
    report.cpp

HEADERS += \
    aircraft.h \
    core_global.h \
    report.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
