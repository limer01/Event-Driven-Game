QT       += core gui \
         multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CS4076_Zork_1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    room.cpp \
    items.cpp \
    task.cpp \
    backpack.cpp

HEADERS  += mainwindow.h \
    room.h \
    items.h \
    delete.h \
    task.h \
    backpack.h

FORMS    += mainwindow.ui

RESOURCES += \
    Resources.qrc
