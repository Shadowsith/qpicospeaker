#-------------------------------------------------
#
# Project created by QtCreator 2018-07-08T02:18:52
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qpicospeaker
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    src/texttospeech.cpp \
    src/aboutinfo.cpp \
    src/qpicospeaker.cpp \
    src/main.cpp \
    src/settings.cpp \
    src/configxml.cpp \
    src/tinyxml2.cpp

HEADERS += \
    src/qpicospeaker.h \
    src/texttospeech.h \
    src/aboutinfo.h \
    src/settings.h \
    src/configxml.h \
    src/tinyxml2.h

FORMS += \
    src/qpicospeaker.ui \
    src/aboutinfo.ui \
    src/settings.ui

TRANSLATIONS += \
    lang/qpicospeaker_en.ts \
    lang/qpicospeaker_es.ts \
    lang/qpicospeaker_de.ts \
    lang/qpicospeaker_fr.ts \
    lang/qpicospeaker_it.ts

DISTFILES += \
    src/qpicospeaker_conf.xml
