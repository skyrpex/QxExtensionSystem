QT = core gui widgets

TARGET = ShitPlugin
TEMPLATE = lib
DESTDIR = $$PWD/../../bin/plugins

include(../../../QxExtensionSystem/QxExtensionSystem.pri)

SOURCES += \
    ShitPlugin.cpp

HEADERS += \
    ShitPlugin.hpp

OTHER_FILES += \
    specs.json
