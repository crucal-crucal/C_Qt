/********************************************************************************
** Form generated from reading UI file 'my_dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MY_DIALOG_H
#define UI_MY_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_My_Dialog
{
public:
    QPushButton *Btn_close;
    QPushButton *Btn_min;
    QLabel *Lab_portrait;
    QLabel *Lab_top;
    QLabel *Lab_mid;
    QLabel *Lab_down;
    QTabWidget *tabWidget;
    QWidget *tabWidgetPage1;
    QWidget *tabWidgetPage2;
    QDateEdit *Edit_date;
    QLabel *Lab_name;
    QLineEdit *Edit_signature;

    void setupUi(QDialog *My_Dialog)
    {
        if (My_Dialog->objectName().isEmpty())
            My_Dialog->setObjectName(QString::fromUtf8("My_Dialog"));
        My_Dialog->resize(300, 600);
        My_Dialog->setStyleSheet(QString::fromUtf8("QPushButton#Btn_close, QPushButton#Btn_min\n"
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
"QLabel#Lab_top\n"
"{\n"
"	background-color: rgb(141, 145, 136);\n"
"}\n"
"QLabel#Lab_mid\n"
"{\n"
"	background-color: rgb(202, 202, 202);\n"
"}\n"
"QLabel#Lab_down\n"
"{\n"
"	background-color: rgb(239, 239, 239);\n"
"}\n"
"QLabel#Lab_name\n"
"{\n"
"	background-color: rgb(141, 145, 136);\n"
"}\n"
"QLineEdit#Edit_signature\n"
"{\n"
"	background-color: rgb(141, 145, 136);\n"
"	font:normal 18px \"\346\245\267\344\275\223\";\n"
"}\n"
"QDateEdit#Edit_date\n"
"{\n"
"	background-color: rgb(141, 145, 136);\n"
"}"));
        Btn_close = new QPushButton(My_Dialog);
        Btn_close->setObjectName(QString::fromUtf8("Btn_close"));
        Btn_close->setGeometry(QRect(270, 0, 30, 30));
        Btn_min = new QPushButton(My_Dialog);
        Btn_min->setObjectName(QString::fromUtf8("Btn_min"));
        Btn_min->setGeometry(QRect(240, 0, 30, 30));
        Lab_portrait = new QLabel(My_Dialog);
        Lab_portrait->setObjectName(QString::fromUtf8("Lab_portrait"));
        Lab_portrait->setGeometry(QRect(10, 50, 50, 50));
        Lab_portrait->setPixmap(QPixmap(QString::fromUtf8(":/images/1 (2).jpg")));
        Lab_portrait->setScaledContents(true);
        Lab_top = new QLabel(My_Dialog);
        Lab_top->setObjectName(QString::fromUtf8("Lab_top"));
        Lab_top->setGeometry(QRect(0, 0, 300, 120));
        Lab_mid = new QLabel(My_Dialog);
        Lab_mid->setObjectName(QString::fromUtf8("Lab_mid"));
        Lab_mid->setGeometry(QRect(0, 120, 300, 20));
        Lab_down = new QLabel(My_Dialog);
        Lab_down->setObjectName(QString::fromUtf8("Lab_down"));
        Lab_down->setGeometry(QRect(40, 160, 300, 460));
        tabWidget = new QTabWidget(My_Dialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 140, 300, 460));
        tabWidgetPage1 = new QWidget();
        tabWidgetPage1->setObjectName(QString::fromUtf8("tabWidgetPage1"));
        tabWidget->addTab(tabWidgetPage1, QString());
        tabWidgetPage2 = new QWidget();
        tabWidgetPage2->setObjectName(QString::fromUtf8("tabWidgetPage2"));
        tabWidget->addTab(tabWidgetPage2, QString());
        Edit_date = new QDateEdit(My_Dialog);
        Edit_date->setObjectName(QString::fromUtf8("Edit_date"));
        Edit_date->setGeometry(QRect(190, 60, 110, 22));
        Lab_name = new QLabel(My_Dialog);
        Lab_name->setObjectName(QString::fromUtf8("Lab_name"));
        Lab_name->setGeometry(QRect(70, 50, 53, 16));
        Edit_signature = new QLineEdit(My_Dialog);
        Edit_signature->setObjectName(QString::fromUtf8("Edit_signature"));
        Edit_signature->setGeometry(QRect(70, 80, 231, 21));
        Lab_top->raise();
        Lab_mid->raise();
        Lab_down->raise();
        Lab_portrait->raise();
        Btn_close->raise();
        Btn_min->raise();
        tabWidget->raise();
        Edit_date->raise();
        Lab_name->raise();
        Edit_signature->raise();

        retranslateUi(My_Dialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(My_Dialog);
    } // setupUi

    void retranslateUi(QDialog *My_Dialog)
    {
        My_Dialog->setWindowTitle(QCoreApplication::translate("My_Dialog", "Dialog", nullptr));
        Btn_close->setText(QString());
        Btn_min->setText(QString());
        Lab_portrait->setText(QString());
        Lab_top->setText(QString());
        Lab_mid->setText(QString());
        Lab_down->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tabWidgetPage1), QString());
        tabWidget->setTabText(tabWidget->indexOf(tabWidgetPage2), QString());
        Lab_name->setText(QCoreApplication::translate("My_Dialog", "crucal", nullptr));
        Edit_signature->setInputMask(QString());
        Edit_signature->setPlaceholderText(QCoreApplication::translate("My_Dialog", "\347\274\226\350\276\221\344\270\252\346\200\247\347\255\276\345\220\215", nullptr));
    } // retranslateUi

};

namespace Ui {
    class My_Dialog: public Ui_My_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MY_DIALOG_H
