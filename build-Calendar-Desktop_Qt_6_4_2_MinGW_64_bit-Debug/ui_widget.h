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
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_12;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *Btn_Time;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QTimeEdit *timeEdit;
    QLineEdit *lineEdit_time;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_3;
    QPushButton *Btn_settime;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QDateEdit *dateEdit;
    QLineEdit *lineEdit_date;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton_6;
    QPushButton *Btn_setdate;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_4;
    QDateTimeEdit *dateTimeEdit;
    QLineEdit *lineEdit_time_date;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *pushButton_7;
    QPushButton *Btn_settd;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_5;
    QLineEdit *lineEdit_cdate;
    QCalendarWidget *calendarWidget;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(614, 269);
        verticalLayout_6 = new QVBoxLayout(Widget);
        verticalLayout_6->setObjectName("verticalLayout_6");
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName("groupBox");
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        Btn_Time = new QPushButton(groupBox);
        Btn_Time->setObjectName("Btn_Time");

        horizontalLayout->addWidget(Btn_Time);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        horizontalLayout_2->addWidget(label);

        timeEdit = new QTimeEdit(groupBox);
        timeEdit->setObjectName("timeEdit");
        timeEdit->setCalendarPopup(false);
        timeEdit->setTimeSpec(Qt::LocalTime);

        horizontalLayout_2->addWidget(timeEdit);

        lineEdit_time = new QLineEdit(groupBox);
        lineEdit_time->setObjectName("lineEdit_time");

        horizontalLayout_2->addWidget(lineEdit_time);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        pushButton_3 = new QPushButton(groupBox);
        pushButton_3->setObjectName("pushButton_3");

        horizontalLayout_3->addWidget(pushButton_3);

        Btn_settime = new QPushButton(groupBox);
        Btn_settime->setObjectName("Btn_settime");

        horizontalLayout_3->addWidget(Btn_settime);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");

        horizontalLayout_4->addWidget(label_3);

        dateEdit = new QDateEdit(groupBox);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setCalendarPopup(true);

        horizontalLayout_4->addWidget(dateEdit);

        lineEdit_date = new QLineEdit(groupBox);
        lineEdit_date->setObjectName("lineEdit_date");

        horizontalLayout_4->addWidget(lineEdit_date);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        pushButton_6 = new QPushButton(groupBox);
        pushButton_6->setObjectName("pushButton_6");

        horizontalLayout_5->addWidget(pushButton_6);

        Btn_setdate = new QPushButton(groupBox);
        Btn_setdate->setObjectName("Btn_setdate");

        horizontalLayout_5->addWidget(Btn_setdate);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");

        horizontalLayout_8->addWidget(label_4);

        dateTimeEdit = new QDateTimeEdit(groupBox);
        dateTimeEdit->setObjectName("dateTimeEdit");

        horizontalLayout_8->addWidget(dateTimeEdit);

        lineEdit_time_date = new QLineEdit(groupBox);
        lineEdit_time_date->setObjectName("lineEdit_time_date");

        horizontalLayout_8->addWidget(lineEdit_time_date);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        pushButton_7 = new QPushButton(groupBox);
        pushButton_7->setObjectName("pushButton_7");

        horizontalLayout_6->addWidget(pushButton_7);

        Btn_settd = new QPushButton(groupBox);
        Btn_settd->setObjectName("Btn_settd");

        horizontalLayout_6->addWidget(Btn_settd);


        verticalLayout->addLayout(horizontalLayout_6);


        verticalLayout_3->addLayout(verticalLayout);


        horizontalLayout_12->addWidget(groupBox);

        groupBox_2 = new QGroupBox(Widget);
        groupBox_2->setObjectName("groupBox_2");
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName("label_5");

        horizontalLayout_11->addWidget(label_5);

        lineEdit_cdate = new QLineEdit(groupBox_2);
        lineEdit_cdate->setObjectName("lineEdit_cdate");

        horizontalLayout_11->addWidget(lineEdit_cdate);


        verticalLayout_5->addLayout(horizontalLayout_11);

        calendarWidget = new QCalendarWidget(groupBox_2);
        calendarWidget->setObjectName("calendarWidget");

        verticalLayout_5->addWidget(calendarWidget);


        verticalLayout_2->addLayout(verticalLayout_5);


        horizontalLayout_12->addWidget(groupBox_2);


        verticalLayout_6->addLayout(horizontalLayout_12);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Widget", "\346\227\245\346\234\237\346\227\266\351\227\264", nullptr));
        Btn_Time->setText(QCoreApplication::translate("Widget", "\350\257\273\345\217\226\345\275\223\345\211\215\346\227\266\351\227\264", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "\345\255\227\347\254\246\344\270\262\346\230\276\347\244\272", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\346\227\266\351\227\264", nullptr));
        timeEdit->setDisplayFormat(QCoreApplication::translate("Widget", "H:mm:ss", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Widget", "qDebug--Time", nullptr));
        Btn_settime->setText(QCoreApplication::translate("Widget", "Set_Time", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "\346\227\245\346\234\237", nullptr));
        dateEdit->setDisplayFormat(QCoreApplication::translate("Widget", "yyyy\345\271\264M\346\234\210d\346\227\245", nullptr));
        pushButton_6->setText(QCoreApplication::translate("Widget", "qDebug--Time", nullptr));
        Btn_setdate->setText(QCoreApplication::translate("Widget", "Set_date", nullptr));
        label_4->setText(QCoreApplication::translate("Widget", "\346\227\245\346\234\237\346\227\266\351\227\264", nullptr));
        dateTimeEdit->setDisplayFormat(QCoreApplication::translate("Widget", "yyyy/M/d H:mm:ss", nullptr));
        pushButton_7->setText(QCoreApplication::translate("Widget", "qDebug--Timedate", nullptr));
        Btn_settd->setText(QCoreApplication::translate("Widget", "Set_time&&date", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Widget", "\346\227\245\345\216\206\351\200\211\346\213\251", nullptr));
        label_5->setText(QCoreApplication::translate("Widget", "\351\200\211\346\213\251\346\227\245\346\234\237\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
