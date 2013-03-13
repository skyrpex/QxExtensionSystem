#pragma once

#include <QPluginLoader>
#include <QString>
#include <QList>
#include <QMap>

class PluginDependency
{
public:
    PluginDependency(const QString &name, const QString &version)
        : name(name),
          version(version)
    {
    }

    PluginDependency(const PluginDependency &other)
        : name(other.name),
          version(other.version)
    {
    }

    bool operator==(const PluginDependency &other) const
    {
        return name == other.name && version == other.version;
    }

    QString name;
    QString version;
};

class QxPlugin;
class PluginHandle;
typedef QList<PluginHandle *> PluginHandleList;

class PluginHandle
{
public:
    PluginHandle();
    ~PluginHandle();
    bool operator==(const PluginHandle &other) const;

    bool load(const QString &path);
    QxPlugin *plugin();

    QString name;
    QString version;
    QList<PluginDependency> dependencies;

private:
    QPluginLoader m_loader;
};
