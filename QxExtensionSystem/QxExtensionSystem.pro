QT       += core gui widgets

TARGET = QxExtensionSystem
TEMPLATE = lib
CONFIG += c++11
DESTDIR = $$PWD/bin
DEFINES += QXEXTENSIONSYSTEM_LIBRARY

INCLUDEPATH *= $$PWD/include

SOURCES += \
    src/QxPluginManager.cpp \
    src/QxPluginManagerPrivate.cpp \
    src/PluginHandle.cpp \
    src/QxPluginPrivate.cpp \
    src/QxPlugin.cpp

HEADERS  += \
    include/QxPlugin.hpp \
    include/QxPluginManager.hpp \
    src/QxPluginManagerPrivate.hpp \
    src/PluginHandle.hpp \
    include/QxExtensionSystemGlobal.hpp \
    src/QxPluginPrivate.hpp
