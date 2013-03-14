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
};

#endif // PLUGINHANDLEPRIVATE_HPP
