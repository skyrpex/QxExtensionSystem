#ifndef QXPLUGINMANAGERPRIVATE_HPP
#define QXPLUGINMANAGERPRIVATE_HPP

#include "PluginHandle.hpp"
#include <QString>
#include <QList>
#include <QObject>

class QxPluginManagerPrivate
{
public:
    QxPluginManagerPrivate();
    ~QxPluginManagerPrivate();

    QList<QxPlugin *> loadPlugins(const QString &path);
    void unloadPlugins();

private:
    void loadHandles(const QString &path);
    void loadQueue();

    bool dependencyCheck(PluginHandle *handle, const PluginHandleList &handles) const;
    bool dependencyCheck(const PluginDependency &dependency, const PluginHandleList &handles) const;

    QObjectList m_pool;
    PluginHandleList m_handles;
    PluginHandleList m_loadQueue;
    PluginHandleList m_noDependenciesQueue;
    QList<QxPlugin *> m_plugins;
};

#endif // QXPLUGINMANAGERPRIVATE_HPP
