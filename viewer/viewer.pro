TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    mainwindow.cpp \
    aircraftmodel.cpp \
    positionmodel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    mainwindow.h \
    aircraftmodel.h \
    positionmodel.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../core/release/ -ladsbData-core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../core/debug/ -ladsbData-core
else:unix: LIBS += -L$$OUT_PWD/../core/ -ladsbData-core

INCLUDEPATH += $$PWD/../core
DEPENDPATH += $$PWD/../core
