#-------------------------------------------------
#
# Project created by QtCreator 2020-07-14T17:47:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = neu202
TEMPLATE = app


SOURCES += main.cpp\
    lms.cpp \
    widget.cpp

HEADERS  += \
    lms.h \
    widget.h

FORMS    += \
    widget.ui
QMAKE_CXXFLAGS += -std=c++0x
