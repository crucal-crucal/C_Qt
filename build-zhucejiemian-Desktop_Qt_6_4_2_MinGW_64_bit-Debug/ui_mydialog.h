/********************************************************************************
** Form generated from reading UI file 'mydialog.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYDIALOG_H
#define UI_MYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_MyDialog
{
public:
    QGroupBox *groupBox_Color;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *Black;
    QRadioButton *Red;
    QRadioButton *Blue;
    QPlainTextEdit *plainTextEdit;
    QGroupBox *groupBox_Font;
    QCheckBox *Xiahuaxian;
    QCheckBox *Xieti;
    QCheckBox *Cuti;
    QPushButton *Clear;
    QPushButton *exit;
    QPushButton *confirm;

    void setupUi(QDialog *MyDialog)
    {
        if (MyDialog->objectName().isEmpty())
            MyDialog->setObjectName("MyDialog");
        MyDialog->resize(901, 613);
        groupBox_Color = new QGroupBox(MyDialog);
        groupBox_Color->setObjectName("groupBox_Color");
        groupBox_Color->setGeometry(QRect(70, 91, 782, 55));
        horizontalLayout_2 = new QHBoxLayout(groupBox_Color);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        Black = new QRadioButton(groupBox_Color);
        Black->setObjectName("Black");

        horizontalLayout_2->addWidget(Black);

        Red = new QRadioButton(groupBox_Color);
        Red->setObjectName("Red");

        horizontalLayout_2->addWidget(Red);

        Blue = new QRadioButton(groupBox_Color);
        Blue->setObjectName("Blue");

        horizontalLayout_2->addWidget(Blue);

        plainTextEdit = new QPlainTextEdit(MyDialog);
        plainTextEdit->setObjectName("plainTextEdit");
        plainTextEdit->setGeometry(QRect(70, 152, 782, 428));
        groupBox_Font = new QGroupBox(MyDialog);
        groupBox_Font->setObjectName("groupBox_Font");
        groupBox_Font->setGeometry(QRect(70, 30, 782, 55));
        Xiahuaxian = new QCheckBox(groupBox_Font);
        Xiahuaxian->setObjectName("Xiahuaxian");
        Xiahuaxian->setGeometry(QRect(10, 25, 79, 20));
        Xieti = new QCheckBox(groupBox_Font);
        Xieti->setObjectName("Xieti");
        Xieti->setGeometry(QRect(266, 25, 50, 20));
        Cuti = new QCheckBox(groupBox_Font);
        Cuti->setObjectName("Cuti");
        Cuti->setGeometry(QRect(522, 25, 50, 20));
        Clear = new QPushButton(MyDialog);
        Clear->setObjectName("Clear");
        Clear->setGeometry(QRect(70, 580, 75, 24));
        exit = new QPushButton(MyDialog);
        exit->setObjectName("exit");
        exit->setGeometry(QRect(430, 580, 75, 24));
        confirm = new QPushButton(MyDialog);
        confirm->setObjectName("confirm");
        confirm->setGeometry(QRect(780, 580, 75, 24));

        retranslateUi(MyDialog);

        QMetaObject::connectSlotsByName(MyDialog);
    } // setupUi

    void retranslateUi(QDialog *MyDialog)
    {
        MyDialog->setWindowTitle(QCoreApplication::translate("MyDialog", "Dialog", nullptr));
        groupBox_Color->setTitle(QCoreApplication::translate("MyDialog", "\351\242\234\350\211\262", nullptr));
        Black->setText(QCoreApplication::translate("MyDialog", "\351\273\221\350\211\262", nullptr));
        Red->setText(QCoreApplication::translate("MyDialog", "\347\272\242\350\211\262", nullptr));
        Blue->setText(QCoreApplication::translate("MyDialog", "\350\223\235\350\211\262", nullptr));
        groupBox_Font->setTitle(QCoreApplication::translate("MyDialog", "\345\255\227\344\275\223", nullptr));
        Xiahuaxian->setText(QCoreApplication::translate("MyDialog", "Underline", nullptr));
        Xieti->setText(QCoreApplication::translate("MyDialog", "Italic", nullptr));
        Cuti->setText(QCoreApplication::translate("MyDialog", "Bold", nullptr));
        Clear->setText(QCoreApplication::translate("MyDialog", "\346\270\205\347\251\272", nullptr));
        exit->setText(QCoreApplication::translate("MyDialog", "\351\200\200\345\207\272", nullptr));
        confirm->setText(QCoreApplication::translate("MyDialog", "\347\241\256\350\256\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyDialog: public Ui_MyDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYDIALOG_H
