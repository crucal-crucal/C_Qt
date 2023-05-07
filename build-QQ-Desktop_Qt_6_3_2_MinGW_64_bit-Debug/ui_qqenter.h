/********************************************************************************
** Form generated from reading UI file 'qqenter.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QQENTER_H
#define UI_QQENTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qqenter
{
public:
    QLabel *label;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QLabel *label_3;
    QPushButton *pushButton_2;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_7;
    QWidget *widget;
    QFormLayout *formLayout;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *verticalSpacer_8;
    QSpacerItem *verticalSpacer;
    QLabel *label_5;
    QLineEdit *lineEdit;
    QLabel *label_4;
    QLineEdit *lineEdit_2;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *qqenter)
    {
        if (qqenter->objectName().isEmpty())
            qqenter->setObjectName(QString::fromUtf8("qqenter"));
        qqenter->resize(400, 300);
        label = new QLabel(qqenter);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(-10, 0, 411, 301));
        label->setStyleSheet(QString::fromUtf8("border-image: url(:/images/background4.jpg);"));
        layoutWidget = new QWidget(qqenter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 30, 336, 222));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton { background-color: #55aaff; border-style: outset; border-width: 2px; border-radius: 10px; border-color: beige; font: bold 14px; min-width: 10em; padding: 6px; }/*i"));

        gridLayout->addWidget(pushButton, 6, 0, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setStyleSheet(QString::fromUtf8("font: 9pt \"Arial\";\n"
"\n"
"font: 18pt \"Arial\";"));

        gridLayout->addWidget(label_3, 0, 0, 1, 2);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton { background-color: #55aaff; border-style: outset; border-width: 2px; border-radius: 10px; border-color: beige; font: bold 14px; min-width: 10em; padding: 6px; }/*i"));

        gridLayout->addWidget(pushButton_2, 6, 1, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_4, 3, 0, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_5, 4, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 5, 0, 1, 1);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_7, 1, 0, 1, 1);

        widget = new QWidget(layoutWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        formLayout = new QFormLayout(widget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(0, QFormLayout::FieldRole, verticalSpacer_6);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(1, QFormLayout::FieldRole, verticalSpacer_8);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(2, QFormLayout::FieldRole, verticalSpacer);

        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix1/Image/20200610004320.png);\n"
""));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        formLayout->setWidget(4, QFormLayout::FieldRole, lineEdit);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix1/Image/20200610004343.png);"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_4);

        lineEdit_2 = new QLineEdit(widget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(5, QFormLayout::FieldRole, lineEdit_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(6, QFormLayout::FieldRole, verticalSpacer_2);


        gridLayout->addWidget(widget, 2, 0, 1, 2);


        retranslateUi(qqenter);

        QMetaObject::connectSlotsByName(qqenter);
    } // setupUi

    void retranslateUi(QWidget *qqenter)
    {
        qqenter->setWindowTitle(QCoreApplication::translate("qqenter", "Form", nullptr));
        label->setText(QString());
        pushButton->setText(QCoreApplication::translate("qqenter", "\347\231\273\345\275\225", nullptr));
        label_3->setText(QCoreApplication::translate("qqenter", "    \345\261\200\345\237\237\347\275\221\350\201\212\345\244\251\347\231\273\345\275\225\347\225\214\351\235\242", nullptr));
        pushButton_2->setText(QCoreApplication::translate("qqenter", "\351\200\200\345\207\272", nullptr));
        label_5->setText(QCoreApplication::translate("qqenter", "\350\264\246\345\217\267", nullptr));
        label_4->setText(QCoreApplication::translate("qqenter", "\345\257\206\347\240\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class qqenter: public Ui_qqenter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QQENTER_H
