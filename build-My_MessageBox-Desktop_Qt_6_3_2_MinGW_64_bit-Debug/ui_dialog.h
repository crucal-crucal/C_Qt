/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *Btn_openfile;
    QPushButton *Btn_openfiles;
    QPushButton *Btn_directory;
    QPushButton *Btn_save;
    QPushButton *Btn_color;
    QPushButton *Btn_font;
    QPushButton *Btn_message;
    QPlainTextEdit *plainTextEdit;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_3;
    QPushButton *Btn_information;
    QPushButton *Btn_question;
    QPushButton *Btn_warning;
    QPushButton *Btn_critical;
    QPushButton *Btn_aboutQt;
    QPushButton *Btn_about;
    QGroupBox *groupBox_3;
    QPushButton *Btn_inptstring;
    QPushButton *Btn_inptint;
    QPushButton *Btn_inptdouble;
    QPushButton *pushButton_10;
    QPushButton *Btn_close;
    QPushButton *Btn_clean;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(411, 500);
        groupBox = new QGroupBox(Dialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(30, 40, 100, 241));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(11, 26, 82, 206));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        Btn_openfile = new QPushButton(layoutWidget);
        Btn_openfile->setObjectName(QString::fromUtf8("Btn_openfile"));

        verticalLayout_2->addWidget(Btn_openfile);

        Btn_openfiles = new QPushButton(layoutWidget);
        Btn_openfiles->setObjectName(QString::fromUtf8("Btn_openfiles"));

        verticalLayout_2->addWidget(Btn_openfiles);

        Btn_directory = new QPushButton(layoutWidget);
        Btn_directory->setObjectName(QString::fromUtf8("Btn_directory"));

        verticalLayout_2->addWidget(Btn_directory);

        Btn_save = new QPushButton(layoutWidget);
        Btn_save->setObjectName(QString::fromUtf8("Btn_save"));

        verticalLayout_2->addWidget(Btn_save);

        Btn_color = new QPushButton(layoutWidget);
        Btn_color->setObjectName(QString::fromUtf8("Btn_color"));

        verticalLayout_2->addWidget(Btn_color);

        Btn_font = new QPushButton(layoutWidget);
        Btn_font->setObjectName(QString::fromUtf8("Btn_font"));

        verticalLayout_2->addWidget(Btn_font);

        Btn_message = new QPushButton(layoutWidget);
        Btn_message->setObjectName(QString::fromUtf8("Btn_message"));

        verticalLayout_2->addWidget(Btn_message);

        plainTextEdit = new QPlainTextEdit(Dialog);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(30, 290, 341, 191));
        groupBox_2 = new QGroupBox(Dialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(140, 40, 101, 241));
        layoutWidget1 = new QWidget(groupBox_2);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 20, 77, 206));
        verticalLayout_3 = new QVBoxLayout(layoutWidget1);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        Btn_information = new QPushButton(layoutWidget1);
        Btn_information->setObjectName(QString::fromUtf8("Btn_information"));

        verticalLayout_3->addWidget(Btn_information);

        Btn_question = new QPushButton(layoutWidget1);
        Btn_question->setObjectName(QString::fromUtf8("Btn_question"));

        verticalLayout_3->addWidget(Btn_question);

        Btn_warning = new QPushButton(layoutWidget1);
        Btn_warning->setObjectName(QString::fromUtf8("Btn_warning"));

        verticalLayout_3->addWidget(Btn_warning);

        Btn_critical = new QPushButton(layoutWidget1);
        Btn_critical->setObjectName(QString::fromUtf8("Btn_critical"));

        verticalLayout_3->addWidget(Btn_critical);

        Btn_aboutQt = new QPushButton(layoutWidget1);
        Btn_aboutQt->setObjectName(QString::fromUtf8("Btn_aboutQt"));

        verticalLayout_3->addWidget(Btn_aboutQt);

        Btn_about = new QPushButton(layoutWidget1);
        Btn_about->setObjectName(QString::fromUtf8("Btn_about"));

        verticalLayout_3->addWidget(Btn_about);

        groupBox_3 = new QGroupBox(Dialog);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(260, 40, 112, 211));
        Btn_inptstring = new QPushButton(groupBox_3);
        Btn_inptstring->setObjectName(QString::fromUtf8("Btn_inptstring"));
        Btn_inptstring->setGeometry(QRect(10, 80, 75, 24));
        Btn_inptint = new QPushButton(groupBox_3);
        Btn_inptint->setObjectName(QString::fromUtf8("Btn_inptint"));
        Btn_inptint->setGeometry(QRect(10, 30, 75, 24));
        Btn_inptdouble = new QPushButton(groupBox_3);
        Btn_inptdouble->setObjectName(QString::fromUtf8("Btn_inptdouble"));
        Btn_inptdouble->setGeometry(QRect(10, 160, 92, 24));
        pushButton_10 = new QPushButton(groupBox_3);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        pushButton_10->setGeometry(QRect(10, 120, 92, 24));
        Btn_close = new QPushButton(Dialog);
        Btn_close->setObjectName(QString::fromUtf8("Btn_close"));
        Btn_close->setGeometry(QRect(340, 260, 31, 24));
        Btn_close->setStyleSheet(QString::fromUtf8("QPushButton#Btn_close\n"
"{\n"
"	image: url(:/1/tuichu.png);\n"
"}"));
        Btn_clean = new QPushButton(Dialog);
        Btn_clean->setObjectName(QString::fromUtf8("Btn_clean"));
        Btn_clean->setGeometry(QRect(310, 260, 21, 24));
        Btn_clean->setStyleSheet(QString::fromUtf8("QPushButton#Btn_clean\n"
"{\n"
"	image: url(:/1/OIP-C.jfif);\n"
"}\n"
"\n"
""));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Dialog", "\346\240\207\345\207\206\345\257\271\350\257\235\346\241\206", nullptr));
        Btn_openfile->setText(QCoreApplication::translate("Dialog", "\346\211\223\345\274\200\344\270\200\344\270\252\346\226\207\344\273\266", nullptr));
        Btn_openfiles->setText(QCoreApplication::translate("Dialog", "\346\211\223\345\274\200\345\244\232\344\270\252\346\226\207\344\273\266", nullptr));
        Btn_directory->setText(QCoreApplication::translate("Dialog", "\351\200\211\346\213\251\345\267\262\346\234\211\347\233\256\345\275\225", nullptr));
        Btn_save->setText(QCoreApplication::translate("Dialog", "\344\277\235\345\255\230\346\226\207\344\273\266", nullptr));
        Btn_color->setText(QCoreApplication::translate("Dialog", "\351\200\211\346\213\251\351\242\234\350\211\262", nullptr));
        Btn_font->setText(QCoreApplication::translate("Dialog", "\351\200\211\346\213\251\345\255\227\344\275\223", nullptr));
        Btn_message->setText(QCoreApplication::translate("Dialog", "\350\277\233\345\272\246\345\257\271\350\257\235\346\241\206", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Dialog", "\346\240\207\345\207\206\346\266\210\346\201\257\346\241\206", nullptr));
        Btn_information->setText(QCoreApplication::translate("Dialog", "information", nullptr));
        Btn_question->setText(QCoreApplication::translate("Dialog", "question", nullptr));
        Btn_warning->setText(QCoreApplication::translate("Dialog", "warning", nullptr));
        Btn_critical->setText(QCoreApplication::translate("Dialog", "critical", nullptr));
        Btn_aboutQt->setText(QCoreApplication::translate("Dialog", "aboutQt", nullptr));
        Btn_about->setText(QCoreApplication::translate("Dialog", "about", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("Dialog", "\346\240\207\345\207\206\350\276\223\345\205\245\345\257\271\350\257\235\346\241\206", nullptr));
        Btn_inptstring->setText(QCoreApplication::translate("Dialog", "\350\276\223\345\205\245\345\255\227\347\254\246\344\270\262", nullptr));
        Btn_inptint->setText(QCoreApplication::translate("Dialog", "\350\276\223\345\205\245\346\225\264\346\225\260", nullptr));
        Btn_inptdouble->setText(QCoreApplication::translate("Dialog", "\350\276\223\345\205\245\346\265\256\347\202\271\346\225\260", nullptr));
        pushButton_10->setText(QCoreApplication::translate("Dialog", "\346\235\241\347\233\256\345\275\225\351\200\211\346\213\251\350\276\223\345\205\245", nullptr));
        Btn_close->setText(QString());
        Btn_clean->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
