QT       -= gui

TARGET = ShitPlugin
TEMPLATE = lib
DESTDIR = $$PWD/../../bin/plugins

include(../../../QxExtensionSystem/QxExtensionSystem.pri)

SOURCES += \
    ShitPlugin.cpp

HEADERS += \
    ShitPlugin.hpp

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

OTHER_FILES += \
    specs.json
