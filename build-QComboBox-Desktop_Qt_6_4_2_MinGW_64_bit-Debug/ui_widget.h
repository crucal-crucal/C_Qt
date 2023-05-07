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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *Btn_initList;
    QPushButton *Btn_cleanList;
    QCheckBox *checkBox;
    QComboBox *comboBox;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_2;
    QPushButton *Btn_initCity;
    QComboBox *comboBox_2;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_6;
    QPushButton *Btn_clean;
    QPlainTextEdit *plainTextEdit;
    QVBoxLayout *verticalLayout_3;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(561, 380);
        verticalLayout_8 = new QVBoxLayout(Widget);
        verticalLayout_8->setObjectName("verticalLayout_8");
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName("groupBox");
        verticalLayout_4 = new QVBoxLayout(groupBox);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        Btn_initList = new QPushButton(groupBox);
        Btn_initList->setObjectName("Btn_initList");

        horizontalLayout->addWidget(Btn_initList);

        Btn_cleanList = new QPushButton(groupBox);
        Btn_cleanList->setObjectName("Btn_cleanList");

        horizontalLayout->addWidget(Btn_cleanList);

        checkBox = new QCheckBox(groupBox);
        checkBox->setObjectName("checkBox");

        horizontalLayout->addWidget(checkBox);


        verticalLayout->addLayout(horizontalLayout);

        comboBox = new QComboBox(groupBox);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");

        verticalLayout->addWidget(comboBox);


        verticalLayout_4->addLayout(verticalLayout);


        horizontalLayout_3->addWidget(groupBox);

        groupBox_2 = new QGroupBox(Widget);
        groupBox_2->setObjectName("groupBox_2");
        verticalLayout_5 = new QVBoxLayout(groupBox_2);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        Btn_initCity = new QPushButton(groupBox_2);
        Btn_initCity->setObjectName("Btn_initCity");

        verticalLayout_2->addWidget(Btn_initCity);

        comboBox_2 = new QComboBox(groupBox_2);
        comboBox_2->setObjectName("comboBox_2");

        verticalLayout_2->addWidget(comboBox_2);


        verticalLayout_5->addLayout(verticalLayout_2);


        horizontalLayout_3->addWidget(groupBox_2);


        verticalLayout_7->addLayout(horizontalLayout_3);

        groupBox_3 = new QGroupBox(Widget);
        groupBox_3->setObjectName("groupBox_3");
        horizontalLayout_2 = new QHBoxLayout(groupBox_3);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        Btn_clean = new QPushButton(groupBox_3);
        Btn_clean->setObjectName("Btn_clean");

        verticalLayout_6->addWidget(Btn_clean);

        plainTextEdit = new QPlainTextEdit(groupBox_3);
        plainTextEdit->setObjectName("plainTextEdit");

        verticalLayout_6->addWidget(plainTextEdit);


        horizontalLayout_2->addLayout(verticalLayout_6);


        verticalLayout_7->addWidget(groupBox_3);


        verticalLayout_8->addLayout(verticalLayout_7);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");

        verticalLayout_8->addLayout(verticalLayout_3);


        retranslateUi(Widget);
        QObject::connect(Btn_cleanList, &QPushButton::clicked, comboBox, qOverload<>(&QComboBox::clear));
        QObject::connect(Btn_clean, &QPushButton::clicked, plainTextEdit, qOverload<>(&QPlainTextEdit::clear));

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "QComboBox\344\275\277\347\224\250", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Widget", "\347\256\200\345\215\225ComboBox", nullptr));
        Btn_initList->setText(QCoreApplication::translate("Widget", "\345\210\235\345\247\213\345\214\226\345\210\227\350\241\250", nullptr));
        Btn_cleanList->setText(QCoreApplication::translate("Widget", "\346\270\205\347\251\272\345\210\227\350\241\250", nullptr));
        checkBox->setText(QCoreApplication::translate("Widget", "\345\217\257\347\274\226\350\276\221", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Widget", "\344\270\212\346\265\267", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("Widget", "\345\214\227\344\272\254", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("Widget", "\345\244\251\346\264\245", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("Widget", "\346\262\263\345\214\227", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("Widget", "\345\261\261\344\270\234", nullptr));
        comboBox->setItemText(5, QCoreApplication::translate("Widget", "\351\231\225\350\245\277", nullptr));

        comboBox->setPlaceholderText(QCoreApplication::translate("Widget", "\345\214\227\344\272\254\345\270\202", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Widget", "\346\234\211\347\224\250\346\210\267\346\225\260\346\215\256\347\232\204ComboBox", nullptr));
        Btn_initCity->setText(QCoreApplication::translate("Widget", "\345\210\235\345\247\213\345\214\226\345\237\216\345\270\202+\345\214\272\345\217\267", nullptr));
        comboBox_2->setPlaceholderText(QCoreApplication::translate("Widget", "\350\257\267\351\200\211\346\213\251\344\270\200\344\270\252\345\237\216\345\270\202", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("Widget", "\344\277\241\346\201\257\346\230\276\347\244\272", nullptr));
        Btn_clean->setText(QCoreApplication::translate("Widget", "\346\270\205\347\251\272\346\226\207\346\234\254\346\241\206", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
