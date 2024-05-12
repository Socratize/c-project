#-------------------------------------------------
#
# Project created by QtCreator 2024-05-07T17:58:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cal
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    simple.cpp \
    integral.cpp \
    matrix.cpp \
    form.cpp

HEADERS  += mainwindow.h \
    simple.h \
    integral.h \
    matrix.h \
    form.h

FORMS    += mainwindow.ui \
    simple.ui \
    integral.ui \
    matrix.ui \
    form.ui
