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
    qDeleteAll(m_handles);
}

QList<QxPlugin *> QxPluginManagerPrivate::loadPlugins(const QString &path)
{
    unloadPlugins();

    loadHandles(path);
    loadQueue();

    QList<QxPlugin *> plugins;
    foreach(PluginHandle *handle, m_loadQueue) {
        QxPlugin *plugin = handle->plugin();
        if(!plugins.contains(plugin)) {
            plugins << plugin;

            plugin->d->pool = &m_pool;
            plugin->initialize();
        }
    }
    return plugins;
}

void QxPluginManagerPrivate::unloadPlugins()
{
    qDeleteAll(m_handles);
    m_handles.clear();
    m_loadQueue.clear();
    m_noDependenciesQueue.clear();
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
    foreach(PluginDependency dependency, handle->dependencies) {
        if(!dependencyCheck(dependency, handles)) {
            return false;
        }
    }
    return true;
}

bool QxPluginManagerPrivate::dependencyCheck(const PluginDependency &dependency, const PluginHandleList &handles) const
{
    foreach(PluginHandle *handle, handles) {
        if(handle->name == dependency.name && handle->version == dependency.version) {
            return true;
        }
    }
    return false;
}
