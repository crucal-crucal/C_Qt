/********************************************************************************
** Form generated from reading UI file 'my_findpasswd.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MY_FINDPASSWD_H
#define UI_MY_FINDPASSWD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_My_findpasswd
{
public:
    QPushButton *Btn_cancel;
    QPushButton *Btn_min;
    QPushButton *Btn_close;

    void setupUi(QDialog *My_findpasswd)
    {
        if (My_findpasswd->objectName().isEmpty())
            My_findpasswd->setObjectName(QString::fromUtf8("My_findpasswd"));
        My_findpasswd->resize(400, 300);
        My_findpasswd->setStyleSheet(QString::fromUtf8("QPushButton#Btn_cancel\n"
"{\n"
"	color: rgb(87, 188, 255);\n"
"}\n"
"QPushButton#Btn_cancel:hover\n"
"{\n"
"	color: rgb(71, 255, 77);\n"
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
"}"));
        Btn_cancel = new QPushButton(My_findpasswd);
        Btn_cancel->setObjectName(QString::fromUtf8("Btn_cancel"));
        Btn_cancel->setGeometry(QRect(330, 280, 75, 24));
        Btn_min = new QPushButton(My_findpasswd);
        Btn_min->setObjectName(QString::fromUtf8("Btn_min"));
        Btn_min->setGeometry(QRect(340, 0, 30, 30));
        Btn_close = new QPushButton(My_findpasswd);
        Btn_close->setObjectName(QString::fromUtf8("Btn_close"));
        Btn_close->setGeometry(QRect(370, 0, 30, 30));

        retranslateUi(My_findpasswd);

        QMetaObject::connectSlotsByName(My_findpasswd);
    } // setupUi

    void retranslateUi(QDialog *My_findpasswd)
    {
        My_findpasswd->setWindowTitle(QCoreApplication::translate("My_findpasswd", "Dialog", nullptr));
        Btn_cancel->setText(QCoreApplication::translate("My_findpasswd", "\345\217\226\346\266\210", nullptr));
        Btn_min->setText(QString());
        Btn_close->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class My_findpasswd: public Ui_My_findpasswd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MY_FINDPASSWD_H
