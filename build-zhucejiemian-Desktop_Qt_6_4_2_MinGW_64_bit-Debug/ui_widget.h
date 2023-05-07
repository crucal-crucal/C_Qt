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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *Lab_photo;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_yonghu_2;
    QLineEdit *lineEdit_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_mima_2;
    QLineEdit *lineEdit_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QComboBox *comboBox_sheng_2;
    QComboBox *comboBox_shi_2;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *Pbt_regist;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pbt_exit;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(800, 600);
        Lab_photo = new QLabel(Widget);
        Lab_photo->setObjectName("Lab_photo");
        Lab_photo->setGeometry(QRect(130, 110, 531, 291));
        widget = new QWidget(Widget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(150, 430, 368, 118));
        horizontalLayout_5 = new QHBoxLayout(widget);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_yonghu_2 = new QLabel(widget);
        label_yonghu_2->setObjectName("label_yonghu_2");

        horizontalLayout->addWidget(label_yonghu_2);

        lineEdit_3 = new QLineEdit(widget);
        lineEdit_3->setObjectName("lineEdit_3");

        horizontalLayout->addWidget(lineEdit_3);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_mima_2 = new QLabel(widget);
        label_mima_2->setObjectName("label_mima_2");

        horizontalLayout_2->addWidget(label_mima_2);

        lineEdit_4 = new QLineEdit(widget);
        lineEdit_4->setObjectName("lineEdit_4");

        horizontalLayout_2->addWidget(lineEdit_4);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_4 = new QLabel(widget);
        label_4->setObjectName("label_4");

        horizontalLayout_3->addWidget(label_4);

        comboBox_sheng_2 = new QComboBox(widget);
        comboBox_sheng_2->addItem(QString());
        comboBox_sheng_2->addItem(QString());
        comboBox_sheng_2->addItem(QString());
        comboBox_sheng_2->setObjectName("comboBox_sheng_2");

        horizontalLayout_3->addWidget(comboBox_sheng_2);

        comboBox_shi_2 = new QComboBox(widget);
        comboBox_shi_2->addItem(QString());
        comboBox_shi_2->addItem(QString());
        comboBox_shi_2->setObjectName("comboBox_shi_2");

        horizontalLayout_3->addWidget(comboBox_shi_2);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        Pbt_regist = new QPushButton(widget);
        Pbt_regist->setObjectName("Pbt_regist");
        Pbt_regist->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_4->addWidget(Pbt_regist);

        horizontalSpacer_5 = new QSpacerItem(108, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        pbt_exit = new QPushButton(widget);
        pbt_exit->setObjectName("pbt_exit");

        horizontalLayout_4->addWidget(pbt_exit);


        verticalLayout->addLayout(horizontalLayout_4);


        horizontalLayout_5->addLayout(verticalLayout);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);


        retranslateUi(Widget);
        QObject::connect(pbt_exit, &QPushButton::clicked, Widget, qOverload<>(&QWidget::close));

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        Lab_photo->setText(QCoreApplication::translate("Widget", "TextLabel", nullptr));
        label_yonghu_2->setText(QCoreApplication::translate("Widget", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_mima_2->setText(QCoreApplication::translate("Widget", "\345\257\206   \347\240\201", nullptr));
        label_4->setText(QCoreApplication::translate("Widget", "\347\216\260\345\261\205\344\275\217\345\234\260\357\274\232", nullptr));
        comboBox_sheng_2->setItemText(0, QCoreApplication::translate("Widget", "\345\233\233\345\267\235", nullptr));
        comboBox_sheng_2->setItemText(1, QCoreApplication::translate("Widget", "\344\272\221\345\215\227", nullptr));
        comboBox_sheng_2->setItemText(2, QCoreApplication::translate("Widget", "\350\264\265\345\267\236", nullptr));

        comboBox_shi_2->setItemText(0, QCoreApplication::translate("Widget", "\346\210\220\351\203\275", nullptr));
        comboBox_shi_2->setItemText(1, QCoreApplication::translate("Widget", "\346\230\206\346\230\216", nullptr));

        Pbt_regist->setText(QCoreApplication::translate("Widget", "\346\217\220\344\272\244\346\263\250\345\206\214", nullptr));
        pbt_exit->setText(QCoreApplication::translate("Widget", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
