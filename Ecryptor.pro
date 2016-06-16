#-------------------------------------------------
#
# Project created by QtCreator 2016-06-10T04:46:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ecryptor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    t_worker.cpp \
    cryptor.cpp

HEADERS  += mainwindow.h \
    t_worker.h \
    cryptor.h
FORMS    += mainwindow.ui
