#-------------------------------------------------
#
# Project created by QtCreator 2018-03-21T10:32:29
#
#-------------------------------------------------

QT       += core gui \
				 multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Atari_Snake
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    snake.cpp \
    gameplay.cpp \
    snakebody.cpp

HEADERS  += dialog.h \
    snake.h \
    gameplay.h \
    snakebody.h

FORMS    += dialog.ui

RESOURCES += \
    sprites.qrc \
    sound.qrc

DISTFILES +=
