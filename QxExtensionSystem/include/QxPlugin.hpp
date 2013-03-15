#pragma once

#include "QxExtensionSystemGlobal.hpp"
#include <QObject>
#include <QList>
#include <QReadLocker>

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

protected:
    void addObject(QObject *object);
    void addAutoReleasedObject(QObject *object);
    void removeObject(QObject *object);
//    T *findObject
    QObjectList pool() const;
    template <typename T> T *component() {
        QReadLocker(&lock());
        foreach (QObject *component, pool()) {
            if (T *result = qobject_cast<T *>(component)) {
                return result;
            }
        }
        return (T *)0;
    }

    template <typename T> QList<T *> components() {
        QReadLocker(&lock());
        QList<T *> results;
        foreach (QObject *component, pool()) {
            if (T *result = qobject_cast<T *>(component)) {
                results << result;
            }
        }
        return results;
    }

private:
    friend class QxPluginManagerPrivate;

    QxPluginPrivate *d;
};

Q_DECLARE_INTERFACE(QxPlugin, "QxPlugin")
