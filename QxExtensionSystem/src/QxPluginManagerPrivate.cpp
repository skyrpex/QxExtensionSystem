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
    // Uninitialize plugins
    foreach(QxPlugin *plugin, m_plugins) {
        plugin->uninitialize();
    }

    // Delete plugin handles
    qDeleteAll(m_handles);
    m_handles.clear();
    m_loadQueue.clear();
    m_noDependenciesQueue.clear();
    m_plugins.clear();

    // Check for undeleted objects
    if(!m_pool.isEmpty()) {
        qWarning() << "Warning:" << m_pool.count() << "object(s) left in the pool";
        foreach(QObject *object, m_pool) {
            qWarning() << object->metaObject()->className() << object->objectName();
        }
        m_pool.clear();
    }
}

void QxPluginManagerPrivate::loadHandles(const QString &path)
{
    // Fetch all possible plugin file paths. Discards duplicate plugins in Unix like
    // lib.so.1, lib.so.1.0, lib.so.1.0.0
    QStringList filePaths;
    QStringList absoluteFilePaths;
    QList<QFileInfo> entryInfoList = QDir(path).entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
    foreach(QFileInfo info, entryInfoList) {
        QString path = info.absolutePath() + info.baseName();
        if(!filePaths.contains(path)) {
            filePaths << path;
            absoluteFilePaths << info.absoluteFilePath();
        }
    }

    foreach(QString path, absoluteFilePaths) {
        PluginHandle *handle = new PluginHandle;

        if(!handle->load(path)) {
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
