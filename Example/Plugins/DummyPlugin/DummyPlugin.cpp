#include "DummyPlugin.hpp"
#include <QDebug>
#include <QWidget>

void DummyPlugin::initialize()
{
    qDebug() << __FUNCTION__ << component<QWidget>();

    QWidget *widget = new QWidget;
    widget->show();
    addAutoReleasedObject(widget);
}

void DummyPlugin::uninitialize()
{
}

Q_PLUGIN_METADATA(IID "QxPlugin")
