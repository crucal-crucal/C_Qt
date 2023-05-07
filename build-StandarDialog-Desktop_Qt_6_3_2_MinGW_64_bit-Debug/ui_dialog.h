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
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QPushButton *pushButton;
    QPlainTextEdit *QPT_edit;
    QPushButton *Btn_color;
    QPushButton *Btn_input;
    QPushButton *Btn_progress;
    QPushButton *Btn_file;
    QPushButton *Btn_existing;
    QPushButton *Btn_save;
    QPushButton *Btn_massage;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(800, 600);
        pushButton = new QPushButton(Dialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 80, 75, 24));
        QPT_edit = new QPlainTextEdit(Dialog);
        QPT_edit->setObjectName(QString::fromUtf8("QPT_edit"));
        QPT_edit->setGeometry(QRect(10, 160, 501, 221));
        Btn_color = new QPushButton(Dialog);
        Btn_color->setObjectName(QString::fromUtf8("Btn_color"));
        Btn_color->setGeometry(QRect(100, 80, 75, 24));
        Btn_input = new QPushButton(Dialog);
        Btn_input->setObjectName(QString::fromUtf8("Btn_input"));
        Btn_input->setGeometry(QRect(200, 80, 75, 24));
        Btn_progress = new QPushButton(Dialog);
        Btn_progress->setObjectName(QString::fromUtf8("Btn_progress"));
        Btn_progress->setGeometry(QRect(300, 80, 75, 24));
        Btn_file = new QPushButton(Dialog);
        Btn_file->setObjectName(QString::fromUtf8("Btn_file"));
        Btn_file->setGeometry(QRect(400, 80, 101, 24));
        Btn_existing = new QPushButton(Dialog);
        Btn_existing->setObjectName(QString::fromUtf8("Btn_existing"));
        Btn_existing->setGeometry(QRect(10, 120, 91, 24));
        Btn_save = new QPushButton(Dialog);
        Btn_save->setObjectName(QString::fromUtf8("Btn_save"));
        Btn_save->setGeometry(QRect(130, 120, 75, 24));
        Btn_massage = new QPushButton(Dialog);
        Btn_massage->setObjectName(QString::fromUtf8("Btn_massage"));
        Btn_massage->setGeometry(QRect(230, 120, 75, 24));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("Dialog", "\345\255\227\344\275\223", nullptr));
        Btn_color->setText(QCoreApplication::translate("Dialog", "\345\255\227\344\275\223\351\242\234\350\211\262", nullptr));
        Btn_input->setText(QCoreApplication::translate("Dialog", "\350\276\223\345\205\245", nullptr));
        Btn_progress->setText(QCoreApplication::translate("Dialog", "\350\277\233\345\272\246\346\235\241", nullptr));
        Btn_file->setText(QCoreApplication::translate("Dialog", "\350\216\267\345\217\226\346\226\207\344\273\266\350\267\257\345\276\204", nullptr));
        Btn_existing->setText(QCoreApplication::translate("Dialog", "\350\216\267\345\217\226\345\275\223\345\211\215\347\233\256\345\275\225", nullptr));
        Btn_save->setText(QCoreApplication::translate("Dialog", "\344\277\235\345\255\230\346\226\207\344\273\266", nullptr));
        Btn_massage->setText(QCoreApplication::translate("Dialog", "\345\257\271\350\257\235\346\241\206", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
