#-------------------------------------------------
#
# Project created by QtCreator 2016-10-09T15:17:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = widget
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    loger.cpp \
    cpu_memory.cpp \
    settingwindow.cpp

HEADERS  += mainwindow.h \
    loger.h \
    cpu_memory.h \
    settingwindow.h

FORMS    += mainwindow.ui \
    settingwindow.ui
