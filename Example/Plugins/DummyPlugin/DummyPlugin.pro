QT =  core gui widgets

TARGET = DummyPlugin
TEMPLATE = lib
DESTDIR = $$PWD/../../bin/plugins

include(../../../QxExtensionSystem/QxExtensionSystem.pri)

SOURCES += DummyPlugin.cpp

HEADERS += DummyPlugin.hpp

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

OTHER_FILES += \
    DummyPlugin.json
