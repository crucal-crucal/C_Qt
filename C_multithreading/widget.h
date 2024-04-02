
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mythread.h"

QT_BEGIN_NAMESPACE

class QLabel;
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget

{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
private:
    int cnt = 0;
    MyThread *mythread;
};

#endif // WIDGET_H
