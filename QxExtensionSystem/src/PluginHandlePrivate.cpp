#include "PluginHandlePrivate.hpp"
#include "PluginHandle.hpp"
#include "QxPlugin.hpp"

#include <QLibrary>
#include <QPluginLoader>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QRegExp>

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
    if(!isValidVersion(version)) {
        return false;
    }

    QVariantList dependencyVariants = specs.value("dependencies").toArray().toVariantList();
    foreach(QVariant dependencyVariant, dependencyVariants) {
        QVariantMap map = dependencyVariant.toMap();
        QString depName = map.value("name").toString();
        QString depVersion = map.value("version").toString();
        dependencies << PluginDependency(depName, depVersion);
    }

    return true;
}

QRegExp &PluginHandlePrivate::versionRegExp()
{
    static QRegExp reg(QLatin1String("([0-9]+)(?:[.]([0-9]+))?(?:[.]([0-9]+))?(?:_([0-9]+))?"));
    return reg;
}

bool PluginHandlePrivate::isValidVersion(const QString &version)
{
    return versionRegExp().exactMatch(version);
}

int PluginHandlePrivate::versionCompare(const QString &version1, const QString &version2)
{
    QRegExp reg1 = versionRegExp();
    QRegExp reg2 = versionRegExp();
    if (!reg1.exactMatch(version1))
        return 0;
    if (!reg2.exactMatch(version2))
        return 0;
    int number1;
    int number2;
    for (int i = 0; i < 4; ++i) {
        number1 = reg1.cap(i+1).toInt();
        number2 = reg2.cap(i+1).toInt();
        if (number1 < number2)
            return -1;
        if (number1 > number2)
            return 1;
    }
    return 0;
}
