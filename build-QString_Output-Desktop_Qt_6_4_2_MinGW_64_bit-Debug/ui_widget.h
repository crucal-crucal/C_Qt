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
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *Edit_num;
    QLabel *label_2;
    QLineEdit *Edit_price;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label_3;
    QLineEdit *Edit_sum;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *Btn_debug;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *Btn_sum;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QSpinBox *Spx_num;
    QLabel *label_8;
    QDoubleSpinBox *Spx_double;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *Edit_DEC;
    QPushButton *Btn_DEC;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QLineEdit *Edit_BIN;
    QPushButton *Btn_BIN;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QLineEdit *Edit_HEX;
    QPushButton *Btn_HEX;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(381, 325);
        verticalLayout_5 = new QVBoxLayout(Widget);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName("groupBox");
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        Edit_num = new QLineEdit(groupBox);
        Edit_num->setObjectName("Edit_num");

        horizontalLayout->addWidget(Edit_num);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        Edit_price = new QLineEdit(groupBox);
        Edit_price->setObjectName("Edit_price");

        horizontalLayout->addWidget(Edit_price);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer = new QSpacerItem(168, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");

        horizontalLayout_2->addWidget(label_3);

        Edit_sum = new QLineEdit(groupBox);
        Edit_sum->setObjectName("Edit_sum");

        horizontalLayout_2->addWidget(Edit_sum);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        Btn_debug = new QPushButton(groupBox);
        Btn_debug->setObjectName("Btn_debug");

        horizontalLayout_3->addWidget(Btn_debug);

        horizontalSpacer_2 = new QSpacerItem(68, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        Btn_sum = new QPushButton(groupBox);
        Btn_sum->setObjectName("Btn_sum");

        horizontalLayout_3->addWidget(Btn_sum);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_7 = new QLabel(groupBox);
        label_7->setObjectName("label_7");

        horizontalLayout_7->addWidget(label_7);

        Spx_num = new QSpinBox(groupBox);
        Spx_num->setObjectName("Spx_num");

        horizontalLayout_7->addWidget(Spx_num);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName("label_8");

        horizontalLayout_7->addWidget(label_8);

        Spx_double = new QDoubleSpinBox(groupBox);
        Spx_double->setObjectName("Spx_double");
        Spx_double->setSingleStep(0.010000000000000);

        horizontalLayout_7->addWidget(Spx_double);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout_7);


        verticalLayout_4->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(17, 14, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);

        groupBox_2 = new QGroupBox(Widget);
        groupBox_2->setObjectName("groupBox_2");
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName("label_4");

        horizontalLayout_4->addWidget(label_4);

        Edit_DEC = new QLineEdit(groupBox_2);
        Edit_DEC->setObjectName("Edit_DEC");

        horizontalLayout_4->addWidget(Edit_DEC);

        Btn_DEC = new QPushButton(groupBox_2);
        Btn_DEC->setObjectName("Btn_DEC");

        horizontalLayout_4->addWidget(Btn_DEC);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName("label_5");

        horizontalLayout_5->addWidget(label_5);

        Edit_BIN = new QLineEdit(groupBox_2);
        Edit_BIN->setObjectName("Edit_BIN");

        horizontalLayout_5->addWidget(Edit_BIN);

        Btn_BIN = new QPushButton(groupBox_2);
        Btn_BIN->setObjectName("Btn_BIN");

        horizontalLayout_5->addWidget(Btn_BIN);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName("label_6");

        horizontalLayout_6->addWidget(label_6);

        Edit_HEX = new QLineEdit(groupBox_2);
        Edit_HEX->setObjectName("Edit_HEX");

        horizontalLayout_6->addWidget(Edit_HEX);

        Btn_HEX = new QPushButton(groupBox_2);
        Btn_HEX->setObjectName("Btn_HEX");

        horizontalLayout_6->addWidget(Btn_HEX);


        verticalLayout->addLayout(horizontalLayout_6);


        verticalLayout_3->addLayout(verticalLayout);


        verticalLayout_4->addWidget(groupBox_2);


        verticalLayout_5->addLayout(verticalLayout_4);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "\345\255\227\347\254\246\344\270\262\344\270\216\346\225\260\345\200\274\344\271\213\351\227\264\347\232\204\350\275\254\346\215\242", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Widget", "\346\225\260\345\200\274\350\276\223\345\205\245\345\222\214\350\276\223\345\207\272", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\346\225\260\351\207\217", nullptr));
        Edit_num->setText(QCoreApplication::translate("Widget", "11", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "\345\215\225\344\273\267", nullptr));
        Edit_price->setText(QCoreApplication::translate("Widget", "1.1", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "\346\200\273\344\273\267", nullptr));
        Btn_debug->setText(QCoreApplication::translate("Widget", "qDebug()\346\265\213\350\257\225", nullptr));
        Btn_sum->setText(QCoreApplication::translate("Widget", "\350\256\241\347\256\227\346\200\273\344\273\267", nullptr));
        label_7->setText(QCoreApplication::translate("Widget", "\346\225\260\351\207\217", nullptr));
        Spx_num->setSuffix(QCoreApplication::translate("Widget", "kg", nullptr));
        label_8->setText(QCoreApplication::translate("Widget", "\345\215\225\344\273\267", nullptr));
        Spx_double->setPrefix(QCoreApplication::translate("Widget", "$", nullptr));
        Spx_double->setSuffix(QString());
        groupBox_2->setTitle(QCoreApplication::translate("Widget", "\350\277\233\345\210\266\350\275\254\346\215\242", nullptr));
        label_4->setText(QCoreApplication::translate("Widget", "DEC", nullptr));
        Edit_DEC->setText(QCoreApplication::translate("Widget", "111", nullptr));
        Btn_DEC->setText(QCoreApplication::translate("Widget", "DEC", nullptr));
        label_5->setText(QCoreApplication::translate("Widget", "BIN", nullptr));
        Btn_BIN->setText(QCoreApplication::translate("Widget", "BIN", nullptr));
        label_6->setText(QCoreApplication::translate("Widget", "HEX", nullptr));
        Btn_HEX->setText(QCoreApplication::translate("Widget", "HEX", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
