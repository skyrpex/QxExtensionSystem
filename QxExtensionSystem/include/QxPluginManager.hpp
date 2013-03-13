#pragma once

#include "QxExtensionSystemGlobal.hpp"
#include "QxPlugin.hpp"
#include <QObject>

class QxPluginManagerPrivate;

class QXEXTENSIONSYSTEM_EXPORT QxPluginManager : public QObject
{
    Q_OBJECT

public:
    QxPluginManager();
    ~QxPluginManager();

    QxPluginList loadPlugins(const QString &path);
    void unloadPlugins();

private:
    QxPluginManagerPrivate *d;
};
