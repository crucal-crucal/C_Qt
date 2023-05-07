/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <mylabel.h>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    MyLabel *lab_butter;
    QPushButton *Btn_music;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(800, 800);
        lab_butter = new MyLabel(Widget);
        lab_butter->setObjectName("lab_butter");
        lab_butter->setGeometry(QRect(70, 130, 221, 161));
        Btn_music = new QPushButton(Widget);
        Btn_music->setObjectName("Btn_music");
        Btn_music->setGeometry(QRect(0, 0, 75, 24));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        lab_butter->setText(QCoreApplication::translate("Widget", "wadawd", nullptr));
        Btn_music->setText(QCoreApplication::translate("Widget", "\346\222\255\346\224\276\351\237\263\344\271\220", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
