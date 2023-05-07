/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *Typeface;
    QHBoxLayout *horizontalLayout;
    QCheckBox *Underline;
    QCheckBox *Italic;
    QCheckBox *Bold;
    QGroupBox *Colour;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *Black;
    QRadioButton *Red;
    QRadioButton *Blue;
    QPlainTextEdit *plainTextEdit;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *Clearn;
    QPushButton *Ok;
    QPushButton *Exit;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(816, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/images/editor.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Widget->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(Widget);
        verticalLayout->setObjectName("verticalLayout");
        Typeface = new QGroupBox(Widget);
        Typeface->setObjectName("Typeface");
        horizontalLayout = new QHBoxLayout(Typeface);
        horizontalLayout->setObjectName("horizontalLayout");
        Underline = new QCheckBox(Typeface);
        Underline->setObjectName("Underline");

        horizontalLayout->addWidget(Underline);

        Italic = new QCheckBox(Typeface);
        Italic->setObjectName("Italic");

        horizontalLayout->addWidget(Italic);

        Bold = new QCheckBox(Typeface);
        Bold->setObjectName("Bold");

        horizontalLayout->addWidget(Bold);


        verticalLayout->addWidget(Typeface);

        Colour = new QGroupBox(Widget);
        Colour->setObjectName("Colour");
        horizontalLayout_2 = new QHBoxLayout(Colour);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        Black = new QRadioButton(Colour);
        Black->setObjectName("Black");

        horizontalLayout_2->addWidget(Black);

        Red = new QRadioButton(Colour);
        Red->setObjectName("Red");

        horizontalLayout_2->addWidget(Red);

        Blue = new QRadioButton(Colour);
        Blue->setObjectName("Blue");

        horizontalLayout_2->addWidget(Blue);


        verticalLayout->addWidget(Colour);

        plainTextEdit = new QPlainTextEdit(Widget);
        plainTextEdit->setObjectName("plainTextEdit");
        QFont font;
        font.setPointSize(20);
        plainTextEdit->setFont(font);

        verticalLayout->addWidget(plainTextEdit);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        Clearn = new QPushButton(Widget);
        Clearn->setObjectName("Clearn");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/images/212.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        Clearn->setIcon(icon1);

        horizontalLayout_3->addWidget(Clearn);

        Ok = new QPushButton(Widget);
        Ok->setObjectName("Ok");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/images/322.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        Ok->setIcon(icon2);

        horizontalLayout_3->addWidget(Ok);

        Exit = new QPushButton(Widget);
        Exit->setObjectName("Exit");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/images/324.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        Exit->setIcon(icon3);

        horizontalLayout_3->addWidget(Exit);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(Widget);
        QObject::connect(Clearn, &QPushButton::clicked, plainTextEdit, qOverload<>(&QPlainTextEdit::clear));
        QObject::connect(Ok, &QPushButton::clicked, Widget, qOverload<>(&QWidget::close));
        QObject::connect(Exit, &QPushButton::clicked, Widget, qOverload<>(&QWidget::close));

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "\344\277\241\345\217\267\345\222\214\346\247\275\347\232\204\344\275\277\347\224\250", nullptr));
        Typeface->setTitle(QCoreApplication::translate("Widget", "\345\255\227\344\275\223", nullptr));
        Underline->setText(QCoreApplication::translate("Widget", "\344\270\213\345\210\222\347\272\277", nullptr));
        Italic->setText(QCoreApplication::translate("Widget", "\346\226\234\344\275\223", nullptr));
        Bold->setText(QCoreApplication::translate("Widget", "\345\212\240\347\262\227", nullptr));
        Colour->setTitle(QCoreApplication::translate("Widget", "\351\242\234\350\211\262", nullptr));
        Black->setText(QCoreApplication::translate("Widget", "\351\273\221\350\211\262", nullptr));
        Red->setText(QCoreApplication::translate("Widget", "\347\272\242", nullptr));
        Blue->setText(QCoreApplication::translate("Widget", "\350\223\235", nullptr));
        plainTextEdit->setPlainText(QCoreApplication::translate("Widget", "Holle QT!", nullptr));
        Clearn->setText(QCoreApplication::translate("Widget", "\346\270\205\347\251\272", nullptr));
        Ok->setText(QCoreApplication::translate("Widget", "\347\241\256\350\256\244", nullptr));
        Exit->setText(QCoreApplication::translate("Widget", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
