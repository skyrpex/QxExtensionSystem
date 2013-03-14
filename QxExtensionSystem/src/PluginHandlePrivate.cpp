#include "PluginHandlePrivate.hpp"
#include "PluginHandle.hpp"
#include "QxPlugin.hpp"

#include <QLibrary>
#include <QPluginLoader>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

PluginHandlePrivate::PluginHandlePrivate()
{
}

PluginHandlePrivate::~PluginHandlePrivate()
{
    loader.unload();
}

bool PluginHandlePrivate::load(const QString &path)
{
    // Check if it's a loadable library
    if(!QLibrary::isLibrary(path)) {
        return false;
    }

    // Setup the plugin loader
    loader.setFileName(path);

    // Load the plugin's meta data
    QJsonObject specs = loader.metaData().value("MetaData").toObject();

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
