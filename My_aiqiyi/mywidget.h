
#ifndef MYWIDGET_H
#define MYWIDGET_H


#include <QEvent>
#include <QLabel>
#include <QPushButton>
#include <QWidget>


class Mywidget : public QWidget
{
    Q_OBJECT
public:
    explicit Mywidget(QWidget *parent = nullptr);

protected:

signals:

public:
    QPushButton *btn1, *btn2, *btn3, *btn4, *btn5, *btn6, *btn7, *btn8, *btn9, *btn10;
    QLabel *label, *lab1;

    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // MYWIDGET_H
