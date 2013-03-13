#ifndef QXPLUGINPRIVATE_HPP
#define QXPLUGINPRIVATE_HPP

#include <QObject>

class QxPluginPrivate
{
public:
    QxPluginPrivate();
    ~QxPluginPrivate();

    QObjectList *pool;
    QObjectList autoReleasePool;
};

#endif // QXPLUGINPRIVATE_HPP
