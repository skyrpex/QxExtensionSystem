#pragma once

#include <QxPlugin.hpp>

class QWidget;

class ShitPlugin : public QxPlugin
{
    Q_INTERFACES(QxPlugin)
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "QxPlugin" FILE "specs.json")

public:
    ShitPlugin(void) {}
    ~ShitPlugin(void) {}

    void initialize();
    void uninitialize();

private:
    QWidget *m_widget;
};
