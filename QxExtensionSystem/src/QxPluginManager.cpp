#include "QxPluginManager.hpp"
#include "QxPluginManagerPrivate.hpp"

QxPluginManager::QxPluginManager()
    : d(new QxPluginManagerPrivate)
{
}

QxPluginManager::~QxPluginManager()
{
    delete d;
}

QxPluginList QxPluginManager::loadPlugins(const QString &path)
{
    return d->loadPlugins(path);
}

void QxPluginManager::unloadPlugins()
{
    d->unloadPlugins();
}
