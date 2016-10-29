#-------------------------------------------------
#
# Project created by QtCreator 2016-10-29T12:53:27
#
#-------------------------------------------------

QT       += core gui
QT += widgets
qtHaveModule(printsupport): QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JuReader
TEMPLATE = app


SOURCES += main.cpp\
        jumainwindow.cpp \
    imageviewer.cpp \
    jubookitem.cpp \
    jubookmodel.cpp

HEADERS  += jumainwindow.h \
    imageviewer.h \
    jubookitem.h \
    jubookmodel.h

FORMS    += jumainwindow.ui

#CONFIG += qt warn_on relase
CONFIG += qt warn_on debug
