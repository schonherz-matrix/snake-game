#-------------------------------------------------
#
# Project created by QtCreator 2019-08-31T16:37:45
#
#-------------------------------------------------

TARGET = matrix-snake-game
TEMPLATE = app

QT += core gui network gamepad widgets multimedia

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        src/bite.cpp \
        src/config.cpp \
        src/main.cpp \
        src/mainwindow.cpp \
        src/matrixscene.cpp \
        src/snake.cpp

HEADERS += \
        src/bite.h \
        src/config.h \
        src/direction.h \
        src/mainwindow.h \
        src/matrixscene.h \
        src/snake.h

FORMS += \
        src/mainwindow.ui

INCLUDEPATH += $$PWD/matrix-simple

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/matrix-simple/mueb
DEPENDPATH += $$PWD/matrix-simple/mueb

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/matrix-simple/mueb/release/libmueb.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/matrix-simple/mueb/debug/libmueb.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/matrix-simple/mueb/release/mueb.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/matrix-simple/mueb/debug/mueb.lib
else:unix: PRE_TARGETDEPS += $$PWD/matrix-simple/mueb/libmueb.a

unix:  LIBS += -L$$PWD/matrix-simple/mueb/ -lmueb