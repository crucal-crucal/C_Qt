/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_Font;
    QHBoxLayout *horizontalLayout;
    QCheckBox *Xiahuaxian;
    QCheckBox *Xieti;
    QCheckBox *Cuti;
    QGroupBox *groupBox_Color;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *Black;
    QRadioButton *Red;
    QRadioButton *Blue;
    QPlainTextEdit *plainTextEdit;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *Clear;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *exit;
    QPushButton *confirm;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName("Dialog");
        Dialog->resize(800, 600);
        verticalLayout = new QVBoxLayout(Dialog);
        verticalLayout->setObjectName("verticalLayout");
        groupBox_Font = new QGroupBox(Dialog);
        groupBox_Font->setObjectName("groupBox_Font");
        horizontalLayout = new QHBoxLayout(groupBox_Font);
        horizontalLayout->setObjectName("horizontalLayout");
        Xiahuaxian = new QCheckBox(groupBox_Font);
        Xiahuaxian->setObjectName("Xiahuaxian");

        horizontalLayout->addWidget(Xiahuaxian);

        Xieti = new QCheckBox(groupBox_Font);
        Xieti->setObjectName("Xieti");

        horizontalLayout->addWidget(Xieti);

        Cuti = new QCheckBox(groupBox_Font);
        Cuti->setObjectName("Cuti");

        horizontalLayout->addWidget(Cuti);


        verticalLayout->addWidget(groupBox_Font);

        groupBox_Color = new QGroupBox(Dialog);
        groupBox_Color->setObjectName("groupBox_Color");
        horizontalLayout_2 = new QHBoxLayout(groupBox_Color);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        Black = new QRadioButton(groupBox_Color);
        Black->setObjectName("Black");

        horizontalLayout_2->addWidget(Black);

        Red = new QRadioButton(groupBox_Color);
        Red->setObjectName("Red");

        horizontalLayout_2->addWidget(Red);

        Blue = new QRadioButton(groupBox_Color);
        Blue->setObjectName("Blue");

        horizontalLayout_2->addWidget(Blue);


        verticalLayout->addWidget(groupBox_Color);

        plainTextEdit = new QPlainTextEdit(Dialog);
        plainTextEdit->setObjectName("plainTextEdit");

        verticalLayout->addWidget(plainTextEdit);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        Clear = new QPushButton(Dialog);
        Clear->setObjectName("Clear");

        horizontalLayout_3->addWidget(Clear);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        exit = new QPushButton(Dialog);
        exit->setObjectName("exit");

        horizontalLayout_3->addWidget(exit);

        confirm = new QPushButton(Dialog);
        confirm->setObjectName("confirm");

        horizontalLayout_3->addWidget(confirm);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(Dialog);
        QObject::connect(Clear, &QPushButton::clicked, plainTextEdit, qOverload<>(&QPlainTextEdit::clear));
        QObject::connect(exit, &QPushButton::clicked, Dialog, qOverload<>(&QDialog::close));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        groupBox_Font->setTitle(QCoreApplication::translate("Dialog", "\345\255\227\344\275\223", nullptr));
        Xiahuaxian->setText(QCoreApplication::translate("Dialog", "Underline", nullptr));
        Xieti->setText(QCoreApplication::translate("Dialog", "Italic", nullptr));
        Cuti->setText(QCoreApplication::translate("Dialog", "Bold", nullptr));
        groupBox_Color->setTitle(QCoreApplication::translate("Dialog", "\351\242\234\350\211\262", nullptr));
        Black->setText(QCoreApplication::translate("Dialog", "\351\273\221\350\211\262", nullptr));
        Red->setText(QCoreApplication::translate("Dialog", "\347\272\242\350\211\262", nullptr));
        Blue->setText(QCoreApplication::translate("Dialog", "\350\223\235\350\211\262", nullptr));
        Clear->setText(QCoreApplication::translate("Dialog", "\346\270\205\347\251\272", nullptr));
        exit->setText(QCoreApplication::translate("Dialog", "\351\200\200\345\207\272", nullptr));
        confirm->setText(QCoreApplication::translate("Dialog", "\347\241\256\350\256\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
