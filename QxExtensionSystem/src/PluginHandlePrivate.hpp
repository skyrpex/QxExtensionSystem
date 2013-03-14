#ifndef PLUGINHANDLEPRIVATE_HPP
#define PLUGINHANDLEPRIVATE_HPP

#include <QPluginLoader>
#include <QString>
#include <QList>
#include <QMap>

class QxPlugin;
class PluginDependency;

class PluginHandlePrivate
{
public:
    PluginHandlePrivate();
    ~PluginHandlePrivate();

    bool load(const QString &path);

    QString name;
    QString version;
    QList<PluginDependency> dependencies;
    QPluginLoader loader;

private:
    static QRegExp &versionRegExp();
    static bool isValidVersion(const QString &version);
    static int versionCompare(const QString &version1, const QString &version2);
};

#endif // PLUGINHANDLEPRIVATE_HPP
