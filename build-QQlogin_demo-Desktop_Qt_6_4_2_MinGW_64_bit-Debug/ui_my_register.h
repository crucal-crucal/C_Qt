/********************************************************************************
** Form generated from reading UI file 'my_register.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MY_REGISTER_H
#define UI_MY_REGISTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_My_register
{
public:
    QPushButton *Btn_cancel;
    QPushButton *Btn_close;
    QPushButton *Btn_min;

    void setupUi(QDialog *My_register)
    {
        if (My_register->objectName().isEmpty())
            My_register->setObjectName("My_register");
        My_register->resize(300, 300);
        My_register->setStyleSheet(QString::fromUtf8("QPushButton#Btn_cancel\n"
"{\n"
"	color: rgb(66, 69, 255);\n"
"}\n"
"QPushButton#Btn_cancel:hover\n"
"{\n"
"	color: rgb(255, 166, 76);\n"
"}\n"
"QPushButton#Btn_close, QPushButton#Btn_min\n"
"{\n"
"	border:one;\n"
"}\n"
"QPushButton#Btn_close\n"
"{\n"
"	image: url(:/images/close(1).png);\n"
"}\n"
"QPushButton#Btn_min\n"
"{\n"
"	image: url(:/images/min(1).png);\n"
"}\n"
"QDialog\n"
"{\n"
"	background-color: rgb(0, 255, 255);\n"
"}"));
        Btn_cancel = new QPushButton(My_register);
        Btn_cancel->setObjectName("Btn_cancel");
        Btn_cancel->setGeometry(QRect(240, 280, 61, 24));
        Btn_close = new QPushButton(My_register);
        Btn_close->setObjectName("Btn_close");
        Btn_close->setGeometry(QRect(270, 0, 30, 30));
        Btn_min = new QPushButton(My_register);
        Btn_min->setObjectName("Btn_min");
        Btn_min->setGeometry(QRect(240, 0, 30, 30));

        retranslateUi(My_register);

        QMetaObject::connectSlotsByName(My_register);
    } // setupUi

    void retranslateUi(QDialog *My_register)
    {
        My_register->setWindowTitle(QCoreApplication::translate("My_register", "Dialog", nullptr));
        Btn_cancel->setText(QCoreApplication::translate("My_register", "\345\217\226\346\266\210", nullptr));
        Btn_close->setText(QString());
        Btn_min->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class My_register: public Ui_My_register {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MY_REGISTER_H
