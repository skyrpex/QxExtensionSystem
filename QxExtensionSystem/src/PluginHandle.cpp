#include "PluginHandle.hpp"
#include "QxPlugin.hpp"
#include "PluginHandlePrivate.hpp"

PluginHandle::PluginHandle()
    : d(new PluginHandlePrivate)
{
}

PluginHandle::~PluginHandle()
{
    delete d;
}

bool PluginHandle::load(const QString &path)
{
    return d->load(path);
}

QxPlugin *PluginHandle::plugin()
{
    return qobject_cast<QxPlugin *>(d->loader.instance());
}

QString PluginHandle::name() const
{
    return d->name;
}

QString PluginHandle::version() const
{
    return d->version;
}

QList<PluginDependency> PluginHandle::dependencies() const
{
    return d->dependencies;
}
