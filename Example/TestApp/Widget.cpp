#include "Widget.hpp"
#include "ui_Widget.h"
#include <QxPlugin.hpp>
#include <QDir>
#include <QDebug>
#include <QFileDialog>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QDir dir = QDir::current();
    dir.cd("plugins");
    ui->path->setText(dir.path());
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_browse_pressed()
{
    QString path = QFileDialog::getExistingDirectory(this, QString(), ui->path->text());
    if(path.isEmpty()) {
        return;
    }

    ui->path->setText(path);
}

void Widget::on_load_pressed()
{
    QString path = ui->path->text();

    ui->listWidget->clear();

    QList<QxPlugin *> plugins = m_manager.loadPlugins(path);
    foreach(QxPlugin *plugin, plugins) {
        ui->listWidget->addItem(plugin->metaObject()->className());
    }
}
