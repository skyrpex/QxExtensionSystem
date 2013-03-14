#include "ShitPlugin.hpp"
#include <QDebug>
#include <QWidget>

void ShitPlugin::initialize()
{
    m_widget = new QWidget;
    m_widget->setWindowTitle("ShitPlugin window");
    m_widget->show();
    addObject(m_widget);
}

void ShitPlugin::uninitialize()
{
    removeObject(m_widget);
    delete m_widget;
}

Q_PLUGIN_METADATA(IID "QxPlugin")
