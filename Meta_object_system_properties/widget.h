#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMetaClassInfo>
#include <QDebug>
#include <iostream>
#include "person.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE


class Widget : public QWidget
{
    Q_OBJECT
    Q_CLASSINFO("author", "cf")
    Q_CLASSINFO("company", "icework")
    Q_CLASSINFO("version", "1.0")
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_Btn_Meta_clicked();

    void on_spinBox_boy_valueChanged(int arg1);

    void on_ageChanged();

    void on_Btn_boy_clicked();

    void on_spinBox_girl_valueChanged(int arg1);

    void on_Btn_girl_clicked();

private:
    person *boy;
    person *girl;
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
