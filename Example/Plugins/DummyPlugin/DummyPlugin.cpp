#include "DummyPlugin.hpp"
#include <QDebug>
#include <QWidget>

void DummyPlugin::initialize()
{
    qDebug() << __FUNCTION__ << this;

    QWidget *widget = new QWidget;
    widget->show();
    addAutoReleasedObject(widget);
}

Q_PLUGIN_METADATA(IID "QxPlugin")
