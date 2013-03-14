#include "QxPluginManagerPrivate.hpp"
#include "QxPlugin.hpp"
#include "PluginHandle.hpp"
#include "QxPluginPrivate.hpp"

#include <QFileInfo>
#include <QDir>
#include <QDebug>

QxPluginManagerPrivate::QxPluginManagerPrivate()
{
}

QxPluginManagerPrivate::~QxPluginManagerPrivate()
{
    unloadPlugins();
}

QList<QxPlugin *> QxPluginManagerPrivate::loadPlugins(const QString &path)
{
    unloadPlugins();

    loadHandles(path);
    loadQueue();

    foreach(PluginHandle *handle, m_loadQueue) {
        QxPlugin *plugin = handle->plugin();
        if(!m_plugins.contains(plugin)) {
            m_plugins << plugin;

            plugin->d->pool = &m_pool;
            plugin->initialize();
        }
    }
    return m_plugins;
}

void QxPluginManagerPrivate::unloadPlugins()
{
    foreach(QxPlugin *plugin, m_plugins) {
        plugin->uninitialize();
    }

    if(!m_pool.isEmpty()) {
        qWarning() << m_pool.count() << "object(s) left in the pool";
    }

    qDeleteAll(m_handles);
    m_handles.clear();
    m_loadQueue.clear();
    m_noDependenciesQueue.clear();
    m_plugins.clear();
}

void QxPluginManagerPrivate::loadHandles(const QString &path)
{
    QList<QFileInfo> entryInfoList = QDir(path).entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
    foreach(QFileInfo info, entryInfoList) {
        PluginHandle *handle = new PluginHandle;

        if(!handle->load(info.absoluteFilePath())) {
            delete handle;
            continue;
        }

        m_handles << handle;
    }
}

void QxPluginManagerPrivate::loadQueue()
{
    PluginHandleList unloadedHandles = m_handles;
    forever {
        int nChanges = 0;

        PluginHandleList::Iterator it = unloadedHandles.begin();
        while(it != unloadedHandles.end()) {
            PluginHandle *handle = *it;
            if(dependencyCheck(handle, m_loadQueue)) {
                m_loadQueue << handle;

                it = unloadedHandles.erase(it);

                ++nChanges;
            }
            else {
                m_noDependenciesQueue << handle;
                ++it;
            }
        }

        if(nChanges == 0) {
            return;
        }
    }
}

bool QxPluginManagerPrivate::dependencyCheck(PluginHandle *handle, const PluginHandleList &handles) const
{
    foreach(PluginDependency dependency, handle->dependencies()) {
        if(!dependencyCheck(dependency, handles)) {
            return false;
        }
    }
    return true;
}

bool QxPluginManagerPrivate::dependencyCheck(const PluginDependency &dependency, const PluginHandleList &handles) const
{
    foreach(PluginHandle *handle, handles) {
        if(handle->name() == dependency.name && handle->version() == dependency.version) {
            return true;
        }
    }
    return false;
}
