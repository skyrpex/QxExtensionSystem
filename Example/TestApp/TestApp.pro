QT       += core gui widgets

TARGET = TestApp
TEMPLATE = app
DESTDIR = $$PWD/../bin

include(../../QxExtensionSystem/QxExtensionSystem.pri)

SOURCES += main.cpp\
        Widget.cpp

HEADERS  += Widget.hpp

FORMS    += Widget.ui
