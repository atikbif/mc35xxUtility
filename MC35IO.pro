#-------------------------------------------------
#
# Project created by QtCreator 2016-08-02T11:09:50
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

CONFIG       += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

RC_ICONS = networking.ico
VERSION = 1.0.0.0
QMAKE_TARGET_COMPANY = Kontel Co
QMAKE_TARGET_PRODUCT = MCConf
QMAKE_TARGET_DESCRIPTION = Modbus Module Configuration Utility
QMAKE_TARGET_COPYRIGHT = Kontel

TARGET = MC35IO
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    abstractgui.cpp \
    modbusprotocol.cpp \
    mcfinder.cpp \
    finderthread.cpp \
    mc3510gui.cpp \
    mc3510scanner.cpp \
    mc3523scanner.cpp \
    mc3523gui.cpp \
    tabai8.cpp \
    tab2dor.cpp \
    tab16di.cpp \
    tabconf.cpp \
    mc3512gui.cpp \
    mc3512scanner.cpp \
    abstractscanner.cpp \
    linkmanager.cpp \
    tab8di.cpp \
    tab8do.cpp \
    mc3513gui.cpp \
    mc3513scanner.cpp \
    mc3514gui.cpp \
    mc3514scanner.cpp \
    mc3520gui.cpp \
    mc3520scanner.cpp \
    mc3521gui.cpp \
    mc3521scanner.cpp \
    tab4di.cpp \
    tab4do.cpp \
    mc3516gui.cpp \
    mc3516scanner.cpp \
    tab2ao.cpp \
    mc3517gui.cpp \
    mc3517scanner.cpp \
    mc3518gui.cpp \
    mc3518scanner.cpp \
    tab16do.cpp \
    mc3511gui.cpp \
    mc3511scanner.cpp \
    mc3525gui.cpp \
    mc3525scanner.cpp \
    mc3556scanner.cpp \
    mc3556gui.cpp \
    tabai16.cpp

HEADERS  += mainwindow.h \
    abstractgui.h \
    modbusprotocol.h \
    mcfinder.h \
    finderthread.h \
    mc3510gui.h \
    mc3510scanner.h \
    mc3523gui.h \
    mc3523scanner.h \
    tabai8.h \
    tab2dor.h \
    tab16di.h \
    tabconf.h \
    mc3512gui.h \
    mc3512scanner.h \
    abstractscanner.h \
    linkmanager.h \
    tab8di.h \
    tab8do.h \
    mc3513gui.h \
    mc3513scanner.h \
    mc3514gui.h \
    mc3514scanner.h \
    mc3520gui.h \
    mc3520scanner.h \
    mc3521gui.h \
    mc3521scanner.h \
    tab4di.h \
    tab4do.h \
    mc3516gui.h \
    mc3516scanner.h \
    tab2ao.h \
    mc3517gui.h \
    mc3517scanner.h \
    mc3518gui.h \
    mc3518scanner.h \
    tab16do.h \
    mc3511gui.h \
    mc3511scanner.h \
    mc3525gui.h \
    mc3525scanner.h \
    mc3556gui.h \
    mc3556scanner.h \
    tabai16.h

FORMS    += mainwindow.ui

DISTFILES += \
    mc35.qmodel

RESOURCES += \
    icons.qrc
