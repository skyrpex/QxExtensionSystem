#pragma once

#include <QxPlugin.hpp>
#include <QDebug>

class DummyPlugin : public QxPlugin
{
    Q_INTERFACES(QxPlugin)
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "QxPlugin" FILE "DummyPlugin.json")

public:
    DummyPlugin() {}
   ~DummyPlugin() {}

    void initialize();
};
