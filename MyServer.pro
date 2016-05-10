#-------------------------------------------------
#
# Project created by QtCreator 2016-04-08T15:24:46
#
#-------------------------------------------------

QT       += core
QT       += network
QT       += sql
QT       -= gui

TARGET = MyServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    myserver.cpp \
    mysql.cpp \
    mysocket.cpp

HEADERS += \
    myserver.h \
    mysql.h \
    mysocket.h
