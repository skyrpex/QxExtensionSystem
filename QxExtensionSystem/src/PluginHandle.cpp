#include "PluginHandle.hpp"
#include "QxPlugin.hpp"

#include <QLibrary>
#include <QPluginLoader>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

PluginHandle::PluginHandle()
{
}

PluginHandle::~PluginHandle()
{
    m_loader.unload();
}

bool PluginHandle::operator ==(const PluginHandle &other) const
{
    return name == other.name && version == other.version;
}

bool PluginHandle::load(const QString &path)
{
    // Check if it's a loadable library
    if(!QLibrary::isLibrary(path)) {
        return false;
    }

    // Setup the plugin loader
    m_loader.setFileName(path);

    // Load the plugin's meta data
    QJsonObject specs = m_loader.metaData().value("MetaData").toObject();

    name = specs.value("name").toString();

    version = specs.value("version").toString();

    QVariantList dependencyVariants = specs.value("dependencies").toArray().toVariantList();
    foreach(QVariant dependencyVariant, dependencyVariants) {
        QVariantMap map = dependencyVariant.toMap();
        QString depName = map.value("name").toString();
        QString depVersion = map.value("version").toString();
        dependencies << PluginDependency(depName, depVersion);
    }

    return true;
}

QxPlugin *PluginHandle::plugin()
{
    return qobject_cast<QxPlugin *>(m_loader.instance());
}
