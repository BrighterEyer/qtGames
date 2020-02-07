#-------------------------------------------------
#
# Project created by QtCreator 2013-10-04T17:42:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GameLevelEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    leveltreeitem.cpp \
    newleveldialog.cpp \
    graphicsblockitem.cpp \
    graphicsblockscene.cpp \
    grounddialog.cpp \
    leveltreewidget.cpp \
    exchangeleveldialog.cpp

HEADERS  += mainwindow.h \
    leveltreeitem.h \
    newleveldialog.h \
    graphicsblockitem.h \
    graphicsblockscene.h \
    grounddialog.h \
    LevelGlobal.h \
    leveltreewidget.h \
    exchangeleveldialog.h

FORMS    += mainwindow.ui \
    newleveldialog.ui \
    grounddialog.ui \
    exchangeleveldialog.ui

RESOURCES += \
    res.qrc

#RC_FILE = Icon.rc

OTHER_FILES += \
    GameLevelEditor.rc

RC_FILE = \
  GameLevelEditor.rc
