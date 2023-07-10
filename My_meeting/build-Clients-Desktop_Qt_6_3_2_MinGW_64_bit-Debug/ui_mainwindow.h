/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QPushButton *endBtn;
    QPushButton *startBtn;
    QPushButton *sendData_btn;
    QPushButton *send_picBtn;
    QPushButton *btn_Audio;
    QPushButton *stopShareBtn;
    QPushButton *shareDesk_btn;
    QLabel *label_shareDesktop;
    QLineEdit *lineEdit;
    QPushButton *btn_sendMessage;
    QTextEdit *textEdit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1027, 607);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 120, 431, 231));
        endBtn = new QPushButton(centralwidget);
        endBtn->setObjectName(QString::fromUtf8("endBtn"));
        endBtn->setGeometry(QRect(10, 80, 80, 24));
        startBtn = new QPushButton(centralwidget);
        startBtn->setObjectName(QString::fromUtf8("startBtn"));
        startBtn->setGeometry(QRect(110, 80, 80, 24));
        sendData_btn = new QPushButton(centralwidget);
        sendData_btn->setObjectName(QString::fromUtf8("sendData_btn"));
        sendData_btn->setGeometry(QRect(210, 80, 89, 21));
        send_picBtn = new QPushButton(centralwidget);
        send_picBtn->setObjectName(QString::fromUtf8("send_picBtn"));
        send_picBtn->setGeometry(QRect(350, 80, 89, 25));
        btn_Audio = new QPushButton(centralwidget);
        btn_Audio->setObjectName(QString::fromUtf8("btn_Audio"));
        btn_Audio->setGeometry(QRect(10, 430, 89, 25));
        stopShareBtn = new QPushButton(centralwidget);
        stopShareBtn->setObjectName(QString::fromUtf8("stopShareBtn"));
        stopShareBtn->setGeometry(QRect(738, 70, 171, 25));
        shareDesk_btn = new QPushButton(centralwidget);
        shareDesk_btn->setObjectName(QString::fromUtf8("shareDesk_btn"));
        shareDesk_btn->setGeometry(QRect(530, 70, 121, 25));
        label_shareDesktop = new QLabel(centralwidget);
        label_shareDesktop->setObjectName(QString::fromUtf8("label_shareDesktop"));
        label_shareDesktop->setGeometry(QRect(520, 110, 451, 241));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(600, 380, 113, 25));
        btn_sendMessage = new QPushButton(centralwidget);
        btn_sendMessage->setObjectName(QString::fromUtf8("btn_sendMessage"));
        btn_sendMessage->setGeometry(QRect(610, 450, 89, 25));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(340, 380, 251, 131));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        endBtn->setText(QCoreApplication::translate("MainWindow", "\347\273\223\346\235\237", nullptr));
        startBtn->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213", nullptr));
        sendData_btn->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        send_picBtn->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\345\210\260\346\234\215\345\212\241\345\231\250", nullptr));
        btn_Audio->setText(QCoreApplication::translate("MainWindow", "Audio", nullptr));
        stopShareBtn->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255\345\205\261\344\272\253", nullptr));
        shareDesk_btn->setText(QCoreApplication::translate("MainWindow", "\345\205\261\344\272\253\345\261\217\345\271\225", nullptr));
        label_shareDesktop->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        btn_sendMessage->setText(QCoreApplication::translate("MainWindow", "send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
