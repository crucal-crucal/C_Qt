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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *spinBox_boy;
    QPushButton *Btn_boy;
    QPushButton *Btn_Meta;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpinBox *spinBox_girl;
    QPushButton *Btn_girl;
    QPushButton *Btn_clear;
    QPlainTextEdit *plainTextEdit;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(714, 542);
        verticalLayout_6 = new QVBoxLayout(Widget);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName("groupBox");
        verticalLayout_4 = new QVBoxLayout(groupBox);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        spinBox_boy = new QSpinBox(groupBox);
        spinBox_boy->setObjectName("spinBox_boy");

        horizontalLayout->addWidget(spinBox_boy);

        Btn_boy = new QPushButton(groupBox);
        Btn_boy->setObjectName("Btn_boy");

        horizontalLayout->addWidget(Btn_boy);

        Btn_Meta = new QPushButton(groupBox);
        Btn_Meta->setObjectName("Btn_Meta");

        horizontalLayout->addWidget(Btn_Meta);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        spinBox_girl = new QSpinBox(groupBox);
        spinBox_girl->setObjectName("spinBox_girl");

        horizontalLayout_2->addWidget(spinBox_girl);

        Btn_girl = new QPushButton(groupBox);
        Btn_girl->setObjectName("Btn_girl");

        horizontalLayout_2->addWidget(Btn_girl);

        Btn_clear = new QPushButton(groupBox);
        Btn_clear->setObjectName("Btn_clear");

        horizontalLayout_2->addWidget(Btn_clear);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_4->addLayout(verticalLayout);


        verticalLayout_5->addWidget(groupBox);

        plainTextEdit = new QPlainTextEdit(Widget);
        plainTextEdit->setObjectName("plainTextEdit");

        verticalLayout_5->addWidget(plainTextEdit);


        verticalLayout_6->addLayout(verticalLayout_5);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");

        verticalLayout_6->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");

        verticalLayout_6->addLayout(verticalLayout_2);


        retranslateUi(Widget);
        QObject::connect(Btn_clear, &QPushButton::clicked, plainTextEdit, qOverload<>(&QPlainTextEdit::clear));

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        groupBox->setTitle(QString());
        label->setText(QCoreApplication::translate("Widget", "Boy", nullptr));
        Btn_boy->setText(QCoreApplication::translate("Widget", "Boy\351\225\277\345\244\247\344\270\200\345\262\201", nullptr));
        Btn_Meta->setText(QCoreApplication::translate("Widget", "\345\205\203\345\257\271\350\261\241\344\277\241\346\201\257", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "Girl", nullptr));
        Btn_girl->setText(QCoreApplication::translate("Widget", "Girl\351\225\277\345\244\247\344\270\200\345\262\201", nullptr));
        Btn_clear->setText(QCoreApplication::translate("Widget", "\346\270\205\347\251\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
