#include "QxPluginPrivate.hpp"

QxPluginPrivate::QxPluginPrivate()
    : pool(nullptr)
{
}

QxPluginPrivate::~QxPluginPrivate()
{
    Q_ASSERT(pool);
    foreach(QObject *object, autoReleasePool) {
        pool->removeOne(object);
    }

    qDeleteAll(autoReleasePool);
}
