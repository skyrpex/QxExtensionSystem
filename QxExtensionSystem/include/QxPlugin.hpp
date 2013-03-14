#pragma once

#include "QxExtensionSystemGlobal.hpp"
#include <QObject>
#include <QList>

class QxObjectPool;
class QxPluginPrivate;
class QxPlugin;
typedef QList<QxPlugin *> QxPluginList;

class QXEXTENSIONSYSTEM_EXPORT QxPlugin : public QObject
{
    Q_OBJECT

public:
    QxPlugin();
    virtual ~QxPlugin();

    virtual void initialize() = 0;
    virtual void uninitialize() = 0;

    void addObject(QObject *object);
    void addAutoReleasedObject(QObject *object);
    void removeObject(QObject *object);

private:
    friend class QxPluginManagerPrivate;

    QxPluginPrivate *d;
};

Q_DECLARE_INTERFACE(QxPlugin, "QxPlugin")
