#-------------------------------------------------
#
# Project created by QtCreator 2015-04-07T19:48:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    welcomeform.cpp \
    uvodform.cpp \
    editorform.cpp \
    automatform.cpp \
    diagramform.cpp

HEADERS  += mainwindow.h \
    welcomeform.h \
    uvodform.h \
    editorform.h \
    automatform.h \
    diagramform.h

FORMS    += mainwindow.ui \
    welcomeform.ui \
    uvodform.ui \
    editorform.ui \
    automatform.ui \
    diagramform.ui

DISTFILES +=

RESOURCES += \
    my_files.qrc
