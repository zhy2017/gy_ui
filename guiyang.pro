#-------------------------------------------------
#
# Project created by QtCreator 2018-03-14T11:43:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = guiyang
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sliderbar.cpp \
    setwidget.cpp \
    vedioaddwidget.cpp \
    flowmeterwidget.cpp \
    curvechart.cpp \
    sectionwidget.cpp \
    accountitem.cpp \
    itemvalue.cpp \
    navwidget.cpp \
    sectionitem.cpp \
    linewidget.cpp \
    lineitem.cpp \
    myslider.cpp \
    editWidget/editsection.cpp \
    editWidget/editline.cpp

HEADERS  += mainwindow.h \
    sliderbar.h \
    setwidget.h \
    vedioaddwidget.h \
    flowmeterwidget.h \
    commonhelper.h \
    curvechart.h \
    sectionwidget.h \
    accountitem.h \
    itemvalue.h \
    navwidget.h \
    sectionitem.h \
    linewidget.h \
    lineitem.h \
    type.h \
    myslider.h \
    editWidget/editsection.h \
    editWidget/editline.h

FORMS    += mainwindow.ui \
    setwidget.ui \
    vedioaddwidget.ui \
    flowmeterwidget.ui \
    sectionwidget.ui \
    itemvalue.ui \
    linewidget.ui \
    editWidget/editsection.ui \
    editWidget/editline.ui

RESOURCES += \
    image.qrc
