#-------------------------------------------------
#
# Project created by QtCreator 2018-09-11T12:27:56
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = tspgui
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    tsp_util.cpp \
    tspview.cpp \
    node.cpp

HEADERS += \
        mainwindow.h \
    tsp_util.h \
    tspview.h \
    node.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix|win32: LIBS += -L$$PWD/../../lib/ -ltsp_solver

INCLUDEPATH += $$PWD/../../solver
DEPENDPATH += $$PWD/../../solver

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../lib/tsp_solver.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/../../lib/libtsp_solver.a

unix|win32: LIBS += -L$$PWD/../../lib/ -lutil

INCLUDEPATH += $$PWD/../../util
DEPENDPATH += $$PWD/../../util

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../lib/util.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/../../lib/libutil.a
