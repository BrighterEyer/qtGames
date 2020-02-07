#-------------------------------------------------
#
# Project created by QtCreator 2019-07-04T13:22:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MySlide
TEMPLATE = app


SOURCES += main.cpp\
        mainscene.cpp \
    choosescene.cpp \
    mypushbutton.cpp \
    myblock.cpp \
    gamecore.cpp \
    record_scene.cpp \
    core.cpp

HEADERS  += mainscene.h \
    choosescene.h \
    mypushbutton.h \
    myblock.h \
    gamecore.h \
    record_scene.h \
    core.h

FORMS    += mainscene.ui \
    gamecore.ui \
    record_scene.ui

RESOURCES += \
    res.qrc
