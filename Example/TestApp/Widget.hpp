#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_browse_pressed();

    void on_load_pressed();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_HPP
