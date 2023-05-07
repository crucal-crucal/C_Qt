/********************************************************************************
** Form generated from reading UI file 'lgoin.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LGOIN_H
#define UI_LGOIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Lgoin
{
public:
    QLabel *Label_top;
    QWidget *widget;
    QPushButton *Btn_Register;
    QPushButton *Btn_Qrcode;
    QPushButton *Btn_login;
    QComboBox *username;
    QLineEdit *passward;
    QLabel *Lab_user;
    QLabel *Lab_passwd;
    QCheckBox *Cbox_lgoin;
    QCheckBox *Cbox_passwd;
    QPushButton *Btn_findpasswd;
    QPushButton *Btn_min;
    QPushButton *Btn_close;
    QLabel *Lab_portrait;

    void setupUi(QWidget *Lgoin)
    {
        if (Lgoin->objectName().isEmpty())
            Lgoin->setObjectName(QString::fromUtf8("Lgoin"));
        Lgoin->resize(430, 330);
        Lgoin->setMinimumSize(QSize(430, 330));
        Lgoin->setMaximumSize(QSize(430, 330));
        Lgoin->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	background-color: rgb(171, 255, 217);\n"
"}\n"
".QWidget\n"
"{\n"
"	background-color: rgb(255, 255, 255);\n"
"}\n"
"QPushButton\n"
"{\n"
"	border:one;\n"
"}\n"
"QPushButton#Btn_min\n"
"{\n"
"	image: url(:/images/min(1).png);\n"
"}\n"
"QPushButton#Btn_close\n"
"{\n"
"	image: url(:/images/close(1).png);\n"
"}\n"
"QPushButton#Btn_min:hover\n"
"{	\n"
"	background-color: rgba(226, 226, 226, 200);\n"
"}\n"
"QPushButton#Btn_close:hover\n"
"{\n"
"	background-color:rgb(255,84,57);\n"
"}\n"
"QPushButton#Btn_login\n"
"{\n"
"	background-color: rgb(0, 196, 255);\n"
"	border-radius:5px;\n"
"	font:normal 18px \"\346\245\267\344\275\223\";\n"
"	color:white;\n"
"}\n"
"QComboBox, QLineEdit\n"
"{\n"
"	border:none;\n"
"	border-bottom:1px solid rgb(229, 229, 229);\n"
" 	font:normal 18px \"\346\245\267\344\275\223\";\n"
"	color: rgb(167, 167, 167);\n"
"}\n"
"QComboBox:hover, QLineEdit:hover\n"
"{\n"
"	border-bottom:1px solid rgb(193, 193, 193);\n"
"}\n"
"QComboBox:focus, QLineEdit:focus\n"
"{\n"
"	border-bottom:1p"
                        "x solid rgb(18, 183, 245);\n"
"}\n"
"QPushButton#Btn_Qrcode\n"
"{\n"
"	image: url(:/images/qrcode.png);\n"
"}\n"
"QPushButton#Btn_Qrcode:hover\n"
"{\n"
"	image: url(:/images/qrcode-hover.png);\n"
"}\n"
"QComboBox::drop-down\n"
"{\n"
"	min-width:25px;\n"
"	border-image: url(:/images/drop-down.png);\n"
"}\n"
"QComboBox::drop-down:hover\n"
"{\n"
"	border-image: url(:/images/drop-down-hover.png);\n"
"}\n"
"QComboBox::drop-down:checked\n"
"{\n"
"	border-image: url(:/images/drop-down-on-hover.png);\n"
"}\n"
"QPushButton#Btn_Register:hover\n"
"{\n"
"	color: rgb(225, 232, 255);\n"
"}\n"
"QPushButton#Btn_findpasswd:hover\n"
"{\n"
"	color:rgb(255, 232, 255);\n"
"}\n"
"QCheckBox#Cbox_lgoin, QCheckBox#Cbox_passwd, QPushButton#Btn_findpasswd,\n"
"QPushButton#Btn_Register\n"
"{\n"
"	color: rgb(202, 202, 202);\n"
"}\n"
"QLabel#Lab_user\n"
"{\n"
"	background-color: rgb(255, 255, 255);\n"
"	image: url(:/images/username.png);\n"
"}\n"
"QLabel#Lab_passwd\n"
"{\n"
"	background-color: rgb(255, 255, 255);\n"
"	image: url(:/images/p"
                        "asswd.png);\n"
"}\n"
""));
        Label_top = new QLabel(Lgoin);
        Label_top->setObjectName(QString::fromUtf8("Label_top"));
        Label_top->setGeometry(QRect(0, 0, 430, 130));
        Label_top->setMinimumSize(QSize(0, 130));
        Label_top->setMaximumSize(QSize(16777215, 130));
        Label_top->setPixmap(QPixmap(QString::fromUtf8(":/images/01e9d25debe9e7a801213853a781cd.gif")));
        widget = new QWidget(Lgoin);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 130, 430, 200));
        Btn_Register = new QPushButton(widget);
        Btn_Register->setObjectName(QString::fromUtf8("Btn_Register"));
        Btn_Register->setGeometry(QRect(0, 170, 75, 24));
        Btn_Qrcode = new QPushButton(widget);
        Btn_Qrcode->setObjectName(QString::fromUtf8("Btn_Qrcode"));
        Btn_Qrcode->setGeometry(QRect(390, 160, 32, 32));
        Btn_Qrcode->setMinimumSize(QSize(32, 32));
        Btn_Qrcode->setMaximumSize(QSize(32, 32));
        Btn_login = new QPushButton(widget);
        Btn_login->setObjectName(QString::fromUtf8("Btn_login"));
        Btn_login->setGeometry(QRect(100, 150, 240, 35));
        Btn_login->setMinimumSize(QSize(240, 35));
        Btn_login->setMaximumSize(QSize(240, 35));
        username = new QComboBox(widget);
        username->setObjectName(QString::fromUtf8("username"));
        username->setGeometry(QRect(110, 30, 240, 30));
        username->setMinimumSize(QSize(240, 30));
        username->setMaximumSize(QSize(240, 30));
        username->setEditable(true);
        passward = new QLineEdit(widget);
        passward->setObjectName(QString::fromUtf8("passward"));
        passward->setGeometry(QRect(110, 80, 240, 30));
        passward->setMinimumSize(QSize(240, 30));
        Lab_user = new QLabel(widget);
        Lab_user->setObjectName(QString::fromUtf8("Lab_user"));
        Lab_user->setGeometry(QRect(90, 40, 20, 20));
        Lab_passwd = new QLabel(widget);
        Lab_passwd->setObjectName(QString::fromUtf8("Lab_passwd"));
        Lab_passwd->setGeometry(QRect(90, 90, 20, 21));
        Cbox_lgoin = new QCheckBox(widget);
        Cbox_lgoin->setObjectName(QString::fromUtf8("Cbox_lgoin"));
        Cbox_lgoin->setGeometry(QRect(110, 121, 71, 20));
        Cbox_passwd = new QCheckBox(widget);
        Cbox_passwd->setObjectName(QString::fromUtf8("Cbox_passwd"));
        Cbox_passwd->setGeometry(QRect(190, 121, 71, 20));
        Btn_findpasswd = new QPushButton(widget);
        Btn_findpasswd->setObjectName(QString::fromUtf8("Btn_findpasswd"));
        Btn_findpasswd->setGeometry(QRect(270, 123, 48, 16));
        Btn_min = new QPushButton(Lgoin);
        Btn_min->setObjectName(QString::fromUtf8("Btn_min"));
        Btn_min->setGeometry(QRect(370, 0, 33, 33));
        Btn_min->setMinimumSize(QSize(33, 33));
        Btn_min->setMaximumSize(QSize(33, 33));
        Btn_close = new QPushButton(Lgoin);
        Btn_close->setObjectName(QString::fromUtf8("Btn_close"));
        Btn_close->setGeometry(QRect(399, 0, 33, 33));
        Btn_close->setMinimumSize(QSize(33, 33));
        Btn_close->setMaximumSize(QSize(33, 33));
        Lab_portrait = new QLabel(Lgoin);
        Lab_portrait->setObjectName(QString::fromUtf8("Lab_portrait"));
        Lab_portrait->setGeometry(QRect(180, 80, 70, 70));
        Lab_portrait->setPixmap(QPixmap(QString::fromUtf8(":/images/1 (2).jpg")));
        Lab_portrait->setScaledContents(true);

        retranslateUi(Lgoin);

        QMetaObject::connectSlotsByName(Lgoin);
    } // setupUi

    void retranslateUi(QWidget *Lgoin)
    {
        Lgoin->setWindowTitle(QCoreApplication::translate("Lgoin", "Lgoin", nullptr));
        Label_top->setText(QString());
        Btn_Register->setText(QCoreApplication::translate("Lgoin", "\346\263\250\345\206\214\350\264\246\345\217\267", nullptr));
        Btn_Qrcode->setText(QString());
        Btn_login->setText(QCoreApplication::translate("Lgoin", "\345\256\211\345\205\250\347\231\273\345\275\225", nullptr));
        username->setCurrentText(QString());
        passward->setPlaceholderText(QCoreApplication::translate("Lgoin", "\345\257\206\347\240\201", nullptr));
        Lab_user->setText(QString());
        Lab_passwd->setText(QString());
        Cbox_lgoin->setText(QCoreApplication::translate("Lgoin", "\350\207\252\345\212\250\347\231\273\345\275\225", nullptr));
        Cbox_passwd->setText(QCoreApplication::translate("Lgoin", "\350\256\260\344\275\217\345\257\206\347\240\201", nullptr));
        Btn_findpasswd->setText(QCoreApplication::translate("Lgoin", "\346\211\276\345\233\236\345\257\206\347\240\201", nullptr));
        Btn_min->setText(QString());
        Btn_close->setText(QString());
        Lab_portrait->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Lgoin: public Ui_Lgoin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LGOIN_H
