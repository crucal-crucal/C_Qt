/********************************************************************************
** Form generated from reading UI file 'tcpserver.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCPSERVER_H
#define UI_TCPSERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TcpServer
{
public:
    QLabel *serverStatusLabel;
    QProgressBar *progressBar;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *serverOpenBtn;
    QPushButton *serverSendBtn;
    QPushButton *serverCloseBtn;

    void setupUi(QDialog *TcpServer)
    {
        if (TcpServer->objectName().isEmpty())
            TcpServer->setObjectName(QString::fromUtf8("TcpServer"));
        TcpServer->resize(450, 200);
        TcpServer->setMinimumSize(QSize(450, 200));
        TcpServer->setMaximumSize(QSize(450, 200));
        TcpServer->setLayoutDirection(Qt::LeftToRight);
        serverStatusLabel = new QLabel(TcpServer);
        serverStatusLabel->setObjectName(QString::fromUtf8("serverStatusLabel"));
        serverStatusLabel->setGeometry(QRect(12, 10, 391, 70));
        QFont font;
        font.setPointSize(12);
        serverStatusLabel->setFont(font);
        progressBar = new QProgressBar(TcpServer);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(20, 100, 350, 20));
        progressBar->setMinimumSize(QSize(320, 20));
        progressBar->setMaximumSize(QSize(320, 20));
        progressBar->setValue(0);
        widget = new QWidget(TcpServer);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(40, 137, 254, 27));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        serverOpenBtn = new QPushButton(widget);
        serverOpenBtn->setObjectName(QString::fromUtf8("serverOpenBtn"));
        serverOpenBtn->setMinimumSize(QSize(80, 25));

        horizontalLayout->addWidget(serverOpenBtn);

        serverSendBtn = new QPushButton(widget);
        serverSendBtn->setObjectName(QString::fromUtf8("serverSendBtn"));
        serverSendBtn->setMinimumSize(QSize(80, 25));

        horizontalLayout->addWidget(serverSendBtn);

        serverCloseBtn = new QPushButton(widget);
        serverCloseBtn->setObjectName(QString::fromUtf8("serverCloseBtn"));
        serverCloseBtn->setMinimumSize(QSize(80, 25));

        horizontalLayout->addWidget(serverCloseBtn);


        retranslateUi(TcpServer);

        QMetaObject::connectSlotsByName(TcpServer);
    } // setupUi

    void retranslateUi(QDialog *TcpServer)
    {
        TcpServer->setWindowTitle(QCoreApplication::translate("TcpServer", "\345\217\221\351\200\201\346\226\271", nullptr));
        serverStatusLabel->setText(QCoreApplication::translate("TcpServer", "\350\257\267\351\200\211\346\213\251\350\246\201\345\217\221\351\200\201\347\232\204\346\226\207\344\273\266", nullptr));
        serverOpenBtn->setText(QCoreApplication::translate("TcpServer", "\346\211\223\345\274\200", nullptr));
        serverSendBtn->setText(QCoreApplication::translate("TcpServer", "\345\217\221\351\200\201", nullptr));
        serverCloseBtn->setText(QCoreApplication::translate("TcpServer", "\345\205\263\351\227\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TcpServer: public Ui_TcpServer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCPSERVER_H
