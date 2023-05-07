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
#include <QtWidgets/QDial>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *horizontalLayout_6;
    QDial *Dial;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QSlider *horizontalSlider;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QScrollBar *horizontalScrollBar;
    QHBoxLayout *horizontalLayout_3;
    QLCDNumber *lcdNumber;
    QRadioButton *R_Btn_Bin;
    QRadioButton *R_Btn_OCT;
    QRadioButton *R_Btn_HEX;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QProgressBar *progressBar;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkBox_Visible;
    QCheckBox *checkBox_inverted;
    QHBoxLayout *horizontalLayout;
    QRadioButton *R_Btn_percentage;
    QRadioButton *R_Btn_point;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(540, 479);
        verticalLayout_5 = new QVBoxLayout(Widget);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName("groupBox");
        horizontalLayout_7 = new QHBoxLayout(groupBox);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        Dial = new QDial(groupBox);
        Dial->setObjectName("Dial");
        Dial->setMaximum(200);
        Dial->setNotchesVisible(true);

        horizontalLayout_6->addWidget(Dial);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        horizontalLayout_4->addWidget(label);

        horizontalSlider = new QSlider(groupBox);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setMinimumSize(QSize(250, 20));
        horizontalSlider->setMaximum(200);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setInvertedAppearance(false);
        horizontalSlider->setInvertedControls(false);
        horizontalSlider->setTickPosition(QSlider::TicksAbove);

        horizontalLayout_4->addWidget(horizontalSlider);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        horizontalLayout_5->addWidget(label_2);

        horizontalScrollBar = new QScrollBar(groupBox);
        horizontalScrollBar->setObjectName("horizontalScrollBar");
        horizontalScrollBar->setMinimumSize(QSize(250, 20));
        horizontalScrollBar->setMaximum(200);
        horizontalScrollBar->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(horizontalScrollBar);


        verticalLayout_3->addLayout(horizontalLayout_5);


        horizontalLayout_6->addLayout(verticalLayout_3);


        horizontalLayout_7->addLayout(horizontalLayout_6);


        verticalLayout_4->addWidget(groupBox);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        lcdNumber = new QLCDNumber(Widget);
        lcdNumber->setObjectName("lcdNumber");
        lcdNumber->setMinimumSize(QSize(250, 100));
        lcdNumber->setDigitCount(10);

        horizontalLayout_3->addWidget(lcdNumber);

        R_Btn_Bin = new QRadioButton(Widget);
        R_Btn_Bin->setObjectName("R_Btn_Bin");

        horizontalLayout_3->addWidget(R_Btn_Bin);

        R_Btn_OCT = new QRadioButton(Widget);
        R_Btn_OCT->setObjectName("R_Btn_OCT");

        horizontalLayout_3->addWidget(R_Btn_OCT);

        R_Btn_HEX = new QRadioButton(Widget);
        R_Btn_HEX->setObjectName("R_Btn_HEX");

        horizontalLayout_3->addWidget(R_Btn_HEX);


        verticalLayout_4->addLayout(horizontalLayout_3);

        groupBox_2 = new QGroupBox(Widget);
        groupBox_2->setObjectName("groupBox_2");
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        progressBar = new QProgressBar(groupBox_2);
        progressBar->setObjectName("progressBar");
        progressBar->setMouseTracking(false);
        progressBar->setTabletTracking(false);
        progressBar->setAcceptDrops(false);
        progressBar->setAutoFillBackground(false);
        progressBar->setMaximum(200);
        progressBar->setValue(10);
        progressBar->setInvertedAppearance(false);

        verticalLayout->addWidget(progressBar);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        checkBox_Visible = new QCheckBox(groupBox_2);
        checkBox_Visible->setObjectName("checkBox_Visible");

        horizontalLayout_2->addWidget(checkBox_Visible);

        checkBox_inverted = new QCheckBox(groupBox_2);
        checkBox_inverted->setObjectName("checkBox_inverted");

        horizontalLayout_2->addWidget(checkBox_inverted);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        R_Btn_percentage = new QRadioButton(groupBox_2);
        R_Btn_percentage->setObjectName("R_Btn_percentage");

        horizontalLayout->addWidget(R_Btn_percentage);

        R_Btn_point = new QRadioButton(groupBox_2);
        R_Btn_point->setObjectName("R_Btn_point");

        horizontalLayout->addWidget(R_Btn_point);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        verticalLayout_4->addWidget(groupBox_2);


        verticalLayout_5->addLayout(verticalLayout_4);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Widget", "\346\273\221\345\212\250\350\276\223\345\205\245", nullptr));
        label->setText(QCoreApplication::translate("Widget", "SliderBar", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "TextLabel", nullptr));
        R_Btn_Bin->setText(QCoreApplication::translate("Widget", "2", nullptr));
        R_Btn_OCT->setText(QCoreApplication::translate("Widget", "8", nullptr));
        R_Btn_HEX->setText(QCoreApplication::translate("Widget", "16", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Widget", "ProgressBar\346\230\276\347\244\272\345\222\214\350\256\276\347\275\256", nullptr));
        checkBox_Visible->setText(QCoreApplication::translate("Widget", "textVisible", nullptr));
        checkBox_inverted->setText(QCoreApplication::translate("Widget", "invertedAppearance", nullptr));
        R_Btn_percentage->setText(QCoreApplication::translate("Widget", "\347\231\276\345\210\206\346\257\224", nullptr));
        R_Btn_point->setText(QCoreApplication::translate("Widget", "\345\275\223\345\211\215\345\200\274", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
