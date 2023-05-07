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
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_time;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *Btn_start;
    QPushButton *Btn_stop;
    QPushButton *Btn_dynamic;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *spinBox;
    QRadioButton *rad_Coarse;
    QRadioButton *rad_Once;
    QGroupBox *groupBox_precise;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *RBtn_precise;
    QRadioButton *RBtn_coarse;
    QRadioButton *RBtn_verycoarse;
    QGroupBox *groupBox_now;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *horizontalLayout_6;
    QLCDNumber *lcdNumber_h;
    QLCDNumber *lcdNumber_m;
    QLCDNumber *lcdNumber_s;
    QLabel *lab_ElapsedTime;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(390, 290);
        horizontalLayout_8 = new QHBoxLayout(Widget);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        groupBox_time = new QGroupBox(Widget);
        groupBox_time->setObjectName("groupBox_time");
        horizontalLayout_4 = new QHBoxLayout(groupBox_time);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        Btn_start = new QPushButton(groupBox_time);
        Btn_start->setObjectName("Btn_start");

        horizontalLayout_3->addWidget(Btn_start);

        Btn_stop = new QPushButton(groupBox_time);
        Btn_stop->setObjectName("Btn_stop");

        horizontalLayout_3->addWidget(Btn_stop);

        Btn_dynamic = new QPushButton(groupBox_time);
        Btn_dynamic->setObjectName("Btn_dynamic");

        horizontalLayout_3->addWidget(Btn_dynamic);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(groupBox_time);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label);

        spinBox = new QSpinBox(groupBox_time);
        spinBox->setObjectName("spinBox");
        spinBox->setMinimum(0);
        spinBox->setMaximum(100000);

        horizontalLayout->addWidget(spinBox);

        rad_Coarse = new QRadioButton(groupBox_time);
        rad_Coarse->setObjectName("rad_Coarse");

        horizontalLayout->addWidget(rad_Coarse);

        rad_Once = new QRadioButton(groupBox_time);
        rad_Once->setObjectName("rad_Once");

        horizontalLayout->addWidget(rad_Once);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_4->addLayout(verticalLayout);


        verticalLayout_2->addWidget(groupBox_time);

        groupBox_precise = new QGroupBox(Widget);
        groupBox_precise->setObjectName("groupBox_precise");
        horizontalLayout_5 = new QHBoxLayout(groupBox_precise);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        RBtn_precise = new QRadioButton(groupBox_precise);
        RBtn_precise->setObjectName("RBtn_precise");

        horizontalLayout_2->addWidget(RBtn_precise);

        RBtn_coarse = new QRadioButton(groupBox_precise);
        RBtn_coarse->setObjectName("RBtn_coarse");

        horizontalLayout_2->addWidget(RBtn_coarse);

        RBtn_verycoarse = new QRadioButton(groupBox_precise);
        RBtn_verycoarse->setObjectName("RBtn_verycoarse");

        horizontalLayout_2->addWidget(RBtn_verycoarse);


        horizontalLayout_5->addLayout(horizontalLayout_2);


        verticalLayout_2->addWidget(groupBox_precise);

        groupBox_now = new QGroupBox(Widget);
        groupBox_now->setObjectName("groupBox_now");
        horizontalLayout_7 = new QHBoxLayout(groupBox_now);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        lcdNumber_h = new QLCDNumber(groupBox_now);
        lcdNumber_h->setObjectName("lcdNumber_h");
        lcdNumber_h->setFrameShape(QFrame::Box);
        lcdNumber_h->setFrameShadow(QFrame::Raised);
        lcdNumber_h->setSmallDecimalPoint(false);
        lcdNumber_h->setProperty("intValue", QVariant(12));

        horizontalLayout_6->addWidget(lcdNumber_h);

        lcdNumber_m = new QLCDNumber(groupBox_now);
        lcdNumber_m->setObjectName("lcdNumber_m");

        horizontalLayout_6->addWidget(lcdNumber_m);

        lcdNumber_s = new QLCDNumber(groupBox_now);
        lcdNumber_s->setObjectName("lcdNumber_s");

        horizontalLayout_6->addWidget(lcdNumber_s);


        horizontalLayout_7->addLayout(horizontalLayout_6);


        verticalLayout_2->addWidget(groupBox_now);

        lab_ElapsedTime = new QLabel(Widget);
        lab_ElapsedTime->setObjectName("lab_ElapsedTime");

        verticalLayout_2->addWidget(lab_ElapsedTime);


        horizontalLayout_8->addLayout(verticalLayout_2);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        groupBox_time->setTitle(QCoreApplication::translate("Widget", "\345\256\232\346\227\266\345\231\250", nullptr));
        Btn_start->setText(QCoreApplication::translate("Widget", "\345\274\200\345\247\213", nullptr));
        Btn_stop->setText(QCoreApplication::translate("Widget", "\345\201\234\346\255\242", nullptr));
        Btn_dynamic->setText(QCoreApplication::translate("Widget", "\345\212\250\346\200\201\345\210\233\345\273\272", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\345\256\232\346\234\237\346\227\266\351\227\264", nullptr));
        spinBox->setSuffix(QCoreApplication::translate("Widget", "ms", nullptr));
        rad_Coarse->setText(QCoreApplication::translate("Widget", "\350\277\236\347\273\255\345\256\232\346\227\266", nullptr));
        rad_Once->setText(QCoreApplication::translate("Widget", "\345\215\225\346\254\241\345\256\232\346\227\266", nullptr));
        groupBox_precise->setTitle(QCoreApplication::translate("Widget", "\345\256\232\346\227\266\345\231\250\347\262\276\345\272\246", nullptr));
        RBtn_precise->setText(QCoreApplication::translate("Widget", "PreciseTimer", nullptr));
        RBtn_coarse->setText(QCoreApplication::translate("Widget", "CoarseTimer", nullptr));
        RBtn_verycoarse->setText(QCoreApplication::translate("Widget", "VeryCoarseTimer", nullptr));
        groupBox_now->setTitle(QCoreApplication::translate("Widget", "\345\275\223\345\211\215\346\227\266\351\227\264\357\274\210\345\260\217\346\227\266\357\274\232\345\210\206\357\274\232\347\247\222\357\274\211", nullptr));
        lab_ElapsedTime->setText(QCoreApplication::translate("Widget", "\346\265\201\351\200\235\347\232\204\346\227\266\351\227\264\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
