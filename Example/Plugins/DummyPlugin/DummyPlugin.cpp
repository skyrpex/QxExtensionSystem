#include "DummyPlugin.hpp"
#include <QDebug>
#include <QWidget>

void DummyPlugin::initialize()
{
    QWidget *widget = new QWidget;
    widget->show();
    addAutoReleasedObject(widget);
}

void DummyPlugin::uninitialize()
{
}

Q_PLUGIN_METADATA(IID "QxPlugin")
