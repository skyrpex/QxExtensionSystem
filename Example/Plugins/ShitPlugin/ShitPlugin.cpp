#include "ShitPlugin.hpp"
#include <QDebug>

void ShitPlugin::initialize()
{
    qDebug() << __FUNCTION__ << this;
}

Q_PLUGIN_METADATA(IID "QxPlugin")
