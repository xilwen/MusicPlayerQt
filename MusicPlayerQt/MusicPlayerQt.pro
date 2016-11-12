#-------------------------------------------------
#
# Project created by QtCreator 2016-10-21T20:51:10
#
#-------------------------------------------------

QT       += core gui multimedia quick quickcontrols2

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MusicPlayerQt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    musicplayer.cpp \
    timer.cpp \
    lyricplayer.cpp

HEADERS  += mainwindow.h \
    musicplayer.h \
    timer.h \
    lyricplayer.h

FORMS    +=

RESOURCES += \
    qml.qrc

DISTFILES +=
