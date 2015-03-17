#-------------------------------------------------
#
# Project created by QtCreator 2015-03-17T16:12:47
#
#-------------------------------------------------

QT       += core

QT       -= gui

INCLUDEPATH += /usr/local/include \
               /usr/local/include/opencv \
               /usr/local/include/opencv2

LIBS += /usr/local/lib/libopencv_highgui.so \
        /usr/local/lib/libopencv_core.so    \
        /usr/local/lib/libopencv_imgproc.so

TARGET = CV_HW2
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

DISTFILES += \
    crash.txt
