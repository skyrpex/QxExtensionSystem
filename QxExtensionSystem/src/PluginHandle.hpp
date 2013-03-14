#pragma once

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

    QString name;
    QString version;
};

class PluginDependency;
class QxPlugin;
class PluginHandlePrivate;

class PluginHandle
{
public:
    PluginHandle();
    ~PluginHandle();

    bool load(const QString &path);
    QxPlugin *plugin();

    QString name() const;
    QString version() const;
    QList<PluginDependency> dependencies() const;

private:
    PluginHandlePrivate *d;
};

typedef QList<PluginHandle *> PluginHandleList;
