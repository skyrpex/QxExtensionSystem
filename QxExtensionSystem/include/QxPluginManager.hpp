#pragma once

#include "QxExtensionSystemGlobal.hpp"
#include "QxPlugin.hpp"
#include <QObject>

class QxPluginManagerPrivate;

class QXEXTENSIONSYSTEM_EXPORT QxPluginManager : public QObject
{
    Q_OBJECT

public:
    static QxPluginManager *instance();

    QxPluginList loadPlugins(const QString &path);
    void unloadPlugins();

private:
    QxPluginManager();
    ~QxPluginManager();

    QxPluginManagerPrivate *d;
};
