/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLineEdit *lineEdit;
    QToolButton *tBtn_Backspace;
    QToolButton *tBtn_Clear;
    QToolButton *tBtn_Clear_all;
    QPushButton *Btn_min;
    QPushButton *Btn_close;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QToolButton *tBtn_MC;
    QToolButton *tBtn_7;
    QToolButton *tBtn_8;
    QToolButton *tBtn_9;
    QToolButton *tBtn_div;
    QToolButton *tBtn_sqrt;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *tBtn_MR;
    QToolButton *tBtn_4;
    QToolButton *tBtn_5;
    QToolButton *tBtn_6;
    QToolButton *tBtn_mul;
    QToolButton *tBtn_pow;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *tBtn_MS;
    QToolButton *tBtn_1;
    QToolButton *tBtn_2;
    QToolButton *tBtn_3;
    QToolButton *tBtn_sub;
    QToolButton *tBtn_pow2;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_4;
    QToolButton *tBtn_Madd;
    QToolButton *tBtn_0;
    QToolButton *tBtn_point;
    QToolButton *tBtn_changes;
    QToolButton *tBtn_add;
    QToolButton *tBtn_equal;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(274, 325);
        Widget->setStyleSheet(QString::fromUtf8("QWidget{\n"
"	border:3px solid red;\n"
"	border-radius:10px;\n"
"	background-color:black;\n"
"	color:black;\n"
"}\n"
"QPushButton{\n"
"	border-color:black;\n"
"}\n"
"QPushButton#Btn_min:hover{	\n"
"	background-color: rgba(226, 226, 226, 200);\n"
"}\n"
"QPushButton#Btn_close:hover{\n"
"	background-color:rgb(255,84,57);\n"
"}\n"
"QToolButton{\n"
"	border-radius:10px;\n"
"	background-color:white;\n"
"}\n"
"QToolButton:hover{\n"
"     border-radius:10px;\n"
"     font-size:17px;\n"
"     background-color:pink;\n"
"     color:yellow;\n"
"}\n"
"QLineEdit{\n"
"	border:2px;\n"
"	border-radius:10px;\n"
"	border-color:rgb(255,255,191);\n"
"	background-color:white;\n"
"}\n"
"QLineEdit:hover{\n"
"	border:2px solid pink;\n"
"	border-radius:10px;\n"
"}"));
        lineEdit = new QLineEdit(Widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(0, 30, 271, 41));
        lineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        tBtn_Backspace = new QToolButton(Widget);
        tBtn_Backspace->setObjectName(QString::fromUtf8("tBtn_Backspace"));
        tBtn_Backspace->setGeometry(QRect(0, 80, 101, 31));
        tBtn_Clear = new QToolButton(Widget);
        tBtn_Clear->setObjectName(QString::fromUtf8("tBtn_Clear"));
        tBtn_Clear->setGeometry(QRect(104, 80, 81, 31));
        tBtn_Clear_all = new QToolButton(Widget);
        tBtn_Clear_all->setObjectName(QString::fromUtf8("tBtn_Clear_all"));
        tBtn_Clear_all->setGeometry(QRect(190, 80, 81, 31));
        Btn_min = new QPushButton(Widget);
        Btn_min->setObjectName(QString::fromUtf8("Btn_min"));
        Btn_min->setGeometry(QRect(170, 0, 51, 24));
        Btn_close = new QPushButton(Widget);
        Btn_close->setObjectName(QString::fromUtf8("Btn_close"));
        Btn_close->setGeometry(QRect(220, 0, 51, 24));
        layoutWidget = new QWidget(Widget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 130, 271, 41));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        tBtn_MC = new QToolButton(layoutWidget);
        tBtn_MC->setObjectName(QString::fromUtf8("tBtn_MC"));
        tBtn_MC->setMinimumSize(QSize(0, 0));

        horizontalLayout->addWidget(tBtn_MC);

        tBtn_7 = new QToolButton(layoutWidget);
        tBtn_7->setObjectName(QString::fromUtf8("tBtn_7"));
        tBtn_7->setMinimumSize(QSize(0, 0));

        horizontalLayout->addWidget(tBtn_7);

        tBtn_8 = new QToolButton(layoutWidget);
        tBtn_8->setObjectName(QString::fromUtf8("tBtn_8"));

        horizontalLayout->addWidget(tBtn_8);

        tBtn_9 = new QToolButton(layoutWidget);
        tBtn_9->setObjectName(QString::fromUtf8("tBtn_9"));

        horizontalLayout->addWidget(tBtn_9);

        tBtn_div = new QToolButton(layoutWidget);
        tBtn_div->setObjectName(QString::fromUtf8("tBtn_div"));

        horizontalLayout->addWidget(tBtn_div);

        tBtn_sqrt = new QToolButton(layoutWidget);
        tBtn_sqrt->setObjectName(QString::fromUtf8("tBtn_sqrt"));

        horizontalLayout->addWidget(tBtn_sqrt);

        layoutWidget1 = new QWidget(Widget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(0, 180, 271, 41));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        tBtn_MR = new QToolButton(layoutWidget1);
        tBtn_MR->setObjectName(QString::fromUtf8("tBtn_MR"));

        horizontalLayout_2->addWidget(tBtn_MR);

        tBtn_4 = new QToolButton(layoutWidget1);
        tBtn_4->setObjectName(QString::fromUtf8("tBtn_4"));

        horizontalLayout_2->addWidget(tBtn_4);

        tBtn_5 = new QToolButton(layoutWidget1);
        tBtn_5->setObjectName(QString::fromUtf8("tBtn_5"));

        horizontalLayout_2->addWidget(tBtn_5);

        tBtn_6 = new QToolButton(layoutWidget1);
        tBtn_6->setObjectName(QString::fromUtf8("tBtn_6"));

        horizontalLayout_2->addWidget(tBtn_6);

        tBtn_mul = new QToolButton(layoutWidget1);
        tBtn_mul->setObjectName(QString::fromUtf8("tBtn_mul"));

        horizontalLayout_2->addWidget(tBtn_mul);

        tBtn_pow = new QToolButton(layoutWidget1);
        tBtn_pow->setObjectName(QString::fromUtf8("tBtn_pow"));

        horizontalLayout_2->addWidget(tBtn_pow);

        layoutWidget2 = new QWidget(Widget);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(0, 230, 271, 41));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        tBtn_MS = new QToolButton(layoutWidget2);
        tBtn_MS->setObjectName(QString::fromUtf8("tBtn_MS"));

        horizontalLayout_3->addWidget(tBtn_MS);

        tBtn_1 = new QToolButton(layoutWidget2);
        tBtn_1->setObjectName(QString::fromUtf8("tBtn_1"));

        horizontalLayout_3->addWidget(tBtn_1);

        tBtn_2 = new QToolButton(layoutWidget2);
        tBtn_2->setObjectName(QString::fromUtf8("tBtn_2"));

        horizontalLayout_3->addWidget(tBtn_2);

        tBtn_3 = new QToolButton(layoutWidget2);
        tBtn_3->setObjectName(QString::fromUtf8("tBtn_3"));

        horizontalLayout_3->addWidget(tBtn_3);

        tBtn_sub = new QToolButton(layoutWidget2);
        tBtn_sub->setObjectName(QString::fromUtf8("tBtn_sub"));

        horizontalLayout_3->addWidget(tBtn_sub);

        tBtn_pow2 = new QToolButton(layoutWidget2);
        tBtn_pow2->setObjectName(QString::fromUtf8("tBtn_pow2"));

        horizontalLayout_3->addWidget(tBtn_pow2);

        layoutWidget3 = new QWidget(Widget);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(0, 280, 271, 41));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        tBtn_Madd = new QToolButton(layoutWidget3);
        tBtn_Madd->setObjectName(QString::fromUtf8("tBtn_Madd"));

        horizontalLayout_4->addWidget(tBtn_Madd);

        tBtn_0 = new QToolButton(layoutWidget3);
        tBtn_0->setObjectName(QString::fromUtf8("tBtn_0"));

        horizontalLayout_4->addWidget(tBtn_0);

        tBtn_point = new QToolButton(layoutWidget3);
        tBtn_point->setObjectName(QString::fromUtf8("tBtn_point"));

        horizontalLayout_4->addWidget(tBtn_point);

        tBtn_changes = new QToolButton(layoutWidget3);
        tBtn_changes->setObjectName(QString::fromUtf8("tBtn_changes"));

        horizontalLayout_4->addWidget(tBtn_changes);

        tBtn_add = new QToolButton(layoutWidget3);
        tBtn_add->setObjectName(QString::fromUtf8("tBtn_add"));

        horizontalLayout_4->addWidget(tBtn_add);

        tBtn_equal = new QToolButton(layoutWidget3);
        tBtn_equal->setObjectName(QString::fromUtf8("tBtn_equal"));

        horizontalLayout_4->addWidget(tBtn_equal);


        retranslateUi(Widget);
        QObject::connect(Btn_close, &QPushButton::clicked, Widget, qOverload<>(&QWidget::close));
        QObject::connect(Btn_min, &QPushButton::clicked, Widget, qOverload<>(&QWidget::showMinimized));

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        tBtn_Backspace->setText(QCoreApplication::translate("Widget", "Backspace", nullptr));
        tBtn_Clear->setText(QCoreApplication::translate("Widget", "Clear", nullptr));
        tBtn_Clear_all->setText(QCoreApplication::translate("Widget", "Clear All", nullptr));
        Btn_min->setText(QString());
        Btn_close->setText(QString());
        tBtn_MC->setText(QCoreApplication::translate("Widget", "MC", nullptr));
        tBtn_7->setText(QCoreApplication::translate("Widget", "7", nullptr));
        tBtn_8->setText(QCoreApplication::translate("Widget", "8", nullptr));
        tBtn_9->setText(QCoreApplication::translate("Widget", "9", nullptr));
        tBtn_div->setText(QCoreApplication::translate("Widget", "...", nullptr));
        tBtn_sqrt->setText(QCoreApplication::translate("Widget", "Sqrt", nullptr));
        tBtn_MR->setText(QCoreApplication::translate("Widget", "MC", nullptr));
        tBtn_4->setText(QCoreApplication::translate("Widget", "4", nullptr));
        tBtn_5->setText(QCoreApplication::translate("Widget", "5", nullptr));
        tBtn_6->setText(QCoreApplication::translate("Widget", "6", nullptr));
        tBtn_mul->setText(QCoreApplication::translate("Widget", "...", nullptr));
        tBtn_pow->setText(QCoreApplication::translate("Widget", "...", nullptr));
        tBtn_MS->setText(QCoreApplication::translate("Widget", "MS", nullptr));
        tBtn_1->setText(QCoreApplication::translate("Widget", "1", nullptr));
        tBtn_2->setText(QCoreApplication::translate("Widget", "2", nullptr));
        tBtn_3->setText(QCoreApplication::translate("Widget", "3", nullptr));
        tBtn_sub->setText(QCoreApplication::translate("Widget", "-", nullptr));
        tBtn_pow2->setText(QCoreApplication::translate("Widget", "1/x", nullptr));
        tBtn_Madd->setText(QCoreApplication::translate("Widget", "M+", nullptr));
        tBtn_0->setText(QCoreApplication::translate("Widget", "0", nullptr));
        tBtn_point->setText(QCoreApplication::translate("Widget", ".", nullptr));
        tBtn_changes->setText(QCoreApplication::translate("Widget", "...", nullptr));
        tBtn_add->setText(QCoreApplication::translate("Widget", "+", nullptr));
        tBtn_equal->setText(QCoreApplication::translate("Widget", "=", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
