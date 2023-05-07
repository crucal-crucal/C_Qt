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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout_10;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *Btn_front;
    QPushButton *Btn_left;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *Btn_first;
    QPushButton *Btn_section;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *Btn_empty;
    QPushButton *Btn_resize;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *Btn_size;
    QPushButton *Btn_fill;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *Btn_index;
    QPushButton *Btn_contains;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *Btn_endswith;
    QPushButton *Btn_count;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *Btn_trimmed;
    QPushButton *Btn_insert;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *Btn_remove;
    QPushButton *Btn_repalce;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_9;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label;
    QComboBox *Cbox_str1;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_2;
    QComboBox *Cbox_str2;
    QLabel *label_3;
    QSpinBox *Spin_num;
    QGroupBox *groupBox_6;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout_7;
    QPushButton *Btn_clear;
    QPlainTextEdit *plainTextEdit;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(578, 451);
        verticalLayout_10 = new QVBoxLayout(Widget);
        verticalLayout_10->setObjectName("verticalLayout_10");
        splitter = new QSplitter(Widget);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName("layoutWidget");
        verticalLayout_5 = new QVBoxLayout(layoutWidget);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(layoutWidget);
        groupBox->setObjectName("groupBox");
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        Btn_front = new QPushButton(groupBox);
        Btn_front->setObjectName("Btn_front");

        horizontalLayout->addWidget(Btn_front);

        Btn_left = new QPushButton(groupBox);
        Btn_left->setObjectName("Btn_left");

        horizontalLayout->addWidget(Btn_left);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        Btn_first = new QPushButton(groupBox);
        Btn_first->setObjectName("Btn_first");

        horizontalLayout_2->addWidget(Btn_first);

        Btn_section = new QPushButton(groupBox);
        Btn_section->setObjectName("Btn_section");

        horizontalLayout_2->addWidget(Btn_section);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_5->addWidget(groupBox);

        groupBox_2 = new QGroupBox(layoutWidget);
        groupBox_2->setObjectName("groupBox_2");
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        Btn_empty = new QPushButton(groupBox_2);
        Btn_empty->setObjectName("Btn_empty");

        horizontalLayout_3->addWidget(Btn_empty);

        Btn_resize = new QPushButton(groupBox_2);
        Btn_resize->setObjectName("Btn_resize");

        horizontalLayout_3->addWidget(Btn_resize);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        Btn_size = new QPushButton(groupBox_2);
        Btn_size->setObjectName("Btn_size");

        horizontalLayout_4->addWidget(Btn_size);

        Btn_fill = new QPushButton(groupBox_2);
        Btn_fill->setObjectName("Btn_fill");

        horizontalLayout_4->addWidget(Btn_fill);


        verticalLayout_2->addLayout(horizontalLayout_4);


        verticalLayout_5->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(layoutWidget);
        groupBox_3->setObjectName("groupBox_3");
        verticalLayout_3 = new QVBoxLayout(groupBox_3);
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        Btn_index = new QPushButton(groupBox_3);
        Btn_index->setObjectName("Btn_index");

        horizontalLayout_5->addWidget(Btn_index);

        Btn_contains = new QPushButton(groupBox_3);
        Btn_contains->setObjectName("Btn_contains");

        horizontalLayout_5->addWidget(Btn_contains);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        Btn_endswith = new QPushButton(groupBox_3);
        Btn_endswith->setObjectName("Btn_endswith");

        horizontalLayout_6->addWidget(Btn_endswith);

        Btn_count = new QPushButton(groupBox_3);
        Btn_count->setObjectName("Btn_count");

        horizontalLayout_6->addWidget(Btn_count);


        verticalLayout_3->addLayout(horizontalLayout_6);


        verticalLayout_5->addWidget(groupBox_3);

        groupBox_5 = new QGroupBox(layoutWidget);
        groupBox_5->setObjectName("groupBox_5");
        verticalLayout_4 = new QVBoxLayout(groupBox_5);
        verticalLayout_4->setObjectName("verticalLayout_4");
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        Btn_trimmed = new QPushButton(groupBox_5);
        Btn_trimmed->setObjectName("Btn_trimmed");

        horizontalLayout_7->addWidget(Btn_trimmed);

        Btn_insert = new QPushButton(groupBox_5);
        Btn_insert->setObjectName("Btn_insert");

        horizontalLayout_7->addWidget(Btn_insert);


        verticalLayout_4->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        Btn_remove = new QPushButton(groupBox_5);
        Btn_remove->setObjectName("Btn_remove");

        horizontalLayout_8->addWidget(Btn_remove);

        Btn_repalce = new QPushButton(groupBox_5);
        Btn_repalce->setObjectName("Btn_repalce");

        horizontalLayout_8->addWidget(Btn_repalce);


        verticalLayout_4->addLayout(horizontalLayout_8);


        verticalLayout_5->addWidget(groupBox_5);

        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName("layoutWidget1");
        verticalLayout_9 = new QVBoxLayout(layoutWidget1);
        verticalLayout_9->setObjectName("verticalLayout_9");
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        groupBox_4 = new QGroupBox(layoutWidget1);
        groupBox_4->setObjectName("groupBox_4");
        verticalLayout_6 = new QVBoxLayout(groupBox_4);
        verticalLayout_6->setObjectName("verticalLayout_6");
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        label = new QLabel(groupBox_4);
        label->setObjectName("label");

        horizontalLayout_9->addWidget(label);

        Cbox_str1 = new QComboBox(groupBox_4);
        Cbox_str1->addItem(QString());
        Cbox_str1->setObjectName("Cbox_str1");

        horizontalLayout_9->addWidget(Cbox_str1);


        verticalLayout_6->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        label_2 = new QLabel(groupBox_4);
        label_2->setObjectName("label_2");

        horizontalLayout_10->addWidget(label_2);

        Cbox_str2 = new QComboBox(groupBox_4);
        Cbox_str2->addItem(QString());
        Cbox_str2->setObjectName("Cbox_str2");

        horizontalLayout_10->addWidget(Cbox_str2);

        label_3 = new QLabel(groupBox_4);
        label_3->setObjectName("label_3");

        horizontalLayout_10->addWidget(label_3);

        Spin_num = new QSpinBox(groupBox_4);
        Spin_num->setObjectName("Spin_num");

        horizontalLayout_10->addWidget(Spin_num);


        verticalLayout_6->addLayout(horizontalLayout_10);


        verticalLayout_9->addWidget(groupBox_4);

        groupBox_6 = new QGroupBox(layoutWidget1);
        groupBox_6->setObjectName("groupBox_6");
        verticalLayout_8 = new QVBoxLayout(groupBox_6);
        verticalLayout_8->setObjectName("verticalLayout_8");
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        Btn_clear = new QPushButton(groupBox_6);
        Btn_clear->setObjectName("Btn_clear");

        verticalLayout_7->addWidget(Btn_clear);

        plainTextEdit = new QPlainTextEdit(groupBox_6);
        plainTextEdit->setObjectName("plainTextEdit");

        verticalLayout_7->addWidget(plainTextEdit);


        verticalLayout_8->addLayout(verticalLayout_7);


        verticalLayout_9->addWidget(groupBox_6);

        splitter->addWidget(layoutWidget1);

        verticalLayout_10->addWidget(splitter);


        retranslateUi(Widget);
        QObject::connect(Btn_clear, &QPushButton::clicked, plainTextEdit, qOverload<>(&QPlainTextEdit::clear));

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "QString\345\270\270\347\224\250\345\212\237\350\203\275", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Widget", "\345\255\227\347\254\246\344\270\262\346\210\252\345\217\226", nullptr));
        Btn_front->setText(QCoreApplication::translate("Widget", "front && back", nullptr));
        Btn_left->setText(QCoreApplication::translate("Widget", "left && right", nullptr));
        Btn_first->setText(QCoreApplication::translate("Widget", "first && last", nullptr));
        Btn_section->setText(QCoreApplication::translate("Widget", "section*", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Widget", "\345\255\230\345\202\250\347\233\270\345\205\263", nullptr));
        Btn_empty->setText(QCoreApplication::translate("Widget", "isNull && isEmpty", nullptr));
        Btn_resize->setText(QCoreApplication::translate("Widget", "resize", nullptr));
        Btn_size->setText(QCoreApplication::translate("Widget", "size && length", nullptr));
        Btn_fill->setText(QCoreApplication::translate("Widget", "fill", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("Widget", "\346\220\234\347\264\242\345\222\214\345\210\244\346\226\255", nullptr));
        Btn_index->setText(QCoreApplication::translate("Widget", "indexOf && lastIndexOf", nullptr));
        Btn_contains->setText(QCoreApplication::translate("Widget", "contains", nullptr));
        Btn_endswith->setText(QCoreApplication::translate("Widget", "endsWith && startsWith", nullptr));
        Btn_count->setText(QCoreApplication::translate("Widget", "count", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("Widget", "\350\275\254\346\215\242\346\210\226\344\277\256\346\224\271", nullptr));
        Btn_trimmed->setText(QCoreApplication::translate("Widget", "trimmed && simplified", nullptr));
        Btn_insert->setText(QCoreApplication::translate("Widget", "insert", nullptr));
        Btn_remove->setText(QCoreApplication::translate("Widget", "remove", nullptr));
        Btn_repalce->setText(QCoreApplication::translate("Widget", "repalce", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("Widget", "\350\276\223\345\205\245", nullptr));
        label->setText(QCoreApplication::translate("Widget", "str1", nullptr));
        Cbox_str1->setItemText(0, QCoreApplication::translate("Widget", "G:\\Qt6Book\\QtSamples", nullptr));

        label_2->setText(QCoreApplication::translate("Widget", "str2", nullptr));
        Cbox_str2->setItemText(0, QCoreApplication::translate("Widget", "\\", nullptr));

        label_3->setText(QCoreApplication::translate("Widget", "\345\217\202\346\225\260", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("Widget", "\347\273\223\346\236\234\346\230\276\347\244\272", nullptr));
        Btn_clear->setText(QCoreApplication::translate("Widget", "clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
