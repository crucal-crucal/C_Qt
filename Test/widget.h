
#ifndef WIDGET_H
#define WIDGET_H

#include <QMouseEvent>
#include <QWidget>



QT_BEGIN_NAMESPACE

class QPushButton;
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget

{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QPushButton *btn;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // WIDGET_H
