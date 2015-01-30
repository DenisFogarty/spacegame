#-------------------------------------------------
#
# Project created by QtCreator 2013-10-02T17:05:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = SpaceGame_alpha
TEMPLATE = app


SOURCES += main.cpp\
        gamewindow.cpp \
    Room.cpp \
    Item.cpp \
    Enemy.cpp \
    Character.cpp \
    Puzzlewidget.cpp \
    pieceslist.cpp \
    MainWindow.cpp

HEADERS  += gamewindow.h \
    Room.h \
    Item.h \
    Enemy.h \
    Character.h \
    mainwindow.h \
    puzzlewidget.h \
    pieceslist.h

FORMS    += gamewindow.ui

RESOURCES += \
    images.qrc \
    sound.qrc \
    music.qrc
