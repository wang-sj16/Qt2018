#-------------------------------------------------
#
# Project created by QtCreator 2018-09-10T13:17:50
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myInsaniquarium
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


SOURCES += \
        main.cpp \
        insaniquarium.cpp \
    gameobject.cpp \
    button.cpp \
    global.cpp \
    fish.cpp \
    alien.cpp \
    food.cpp \
    bonus.cpp \
    pet.cpp \
    moneydigit.cpp

HEADERS += \
        insaniquarium.h \
    gameobject.h \
    button.h \
    global.h \
    fish.h \
    alien.h \
    food.h \
    bonus.h \
    pet.h \
    moneydigit.h

RESOURCES += \
    rc.qrc

DISTFILES += \
    ../../myInsaniquarium/Dirty Orchestra - Black Violin.mp3

CONFIG += resources_big
