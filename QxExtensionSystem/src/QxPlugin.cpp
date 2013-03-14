#include "QxPlugin.hpp"
#include "QxPluginPrivate.hpp"

QxPlugin::QxPlugin()
    : d(new QxPluginPrivate)
{

}

QxPlugin::~QxPlugin()
{
    delete d;
}

void QxPlugin::addObject(QObject *object)
{
    d->pool->append(object);
}

void QxPlugin::addAutoReleasedObject(QObject *object)
{
    d->pool->append(object);
    d->autoReleasePool.prepend(object);
}

void QxPlugin::removeObject(QObject *object)
{
    d->pool->removeOne(object);
}
