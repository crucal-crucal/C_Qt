/********************************************************************************
** Form generated from reading UI file 'tcpclient.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCPCLIENT_H
#define UI_TCPCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tcpclient
{
public:
    QLabel *tcpClientStatusLabel;
    QProgressBar *progressBar;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *tcpClientCloseBtn;
    QPushButton *tcpClientCancleBtn;

    void setupUi(QDialog *tcpclient)
    {
        if (tcpclient->objectName().isEmpty())
            tcpclient->setObjectName(QString::fromUtf8("tcpclient"));
        tcpclient->resize(450, 200);
        tcpclient->setMinimumSize(QSize(450, 200));
        tcpclient->setMaximumSize(QSize(450, 200));
        QFont font;
        font.setFamilies({QString::fromUtf8("ADMUI3Lg")});
        font.setPointSize(9);
        tcpclient->setFont(font);
        tcpClientStatusLabel = new QLabel(tcpclient);
        tcpClientStatusLabel->setObjectName(QString::fromUtf8("tcpClientStatusLabel"));
        tcpClientStatusLabel->setGeometry(QRect(30, 10, 381, 70));
        QFont font1;
        font1.setPointSize(12);
        tcpClientStatusLabel->setFont(font1);
        progressBar = new QProgressBar(tcpclient);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(30, 100, 320, 20));
        progressBar->setMinimumSize(QSize(320, 20));
        progressBar->setMaximumSize(QSize(320, 20));
        progressBar->setValue(0);
        widget = new QWidget(tcpclient);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(100, 133, 168, 27));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        tcpClientCloseBtn = new QPushButton(widget);
        tcpClientCloseBtn->setObjectName(QString::fromUtf8("tcpClientCloseBtn"));
        tcpClientCloseBtn->setMinimumSize(QSize(80, 25));

        horizontalLayout->addWidget(tcpClientCloseBtn);

        tcpClientCancleBtn = new QPushButton(widget);
        tcpClientCancleBtn->setObjectName(QString::fromUtf8("tcpClientCancleBtn"));
        tcpClientCancleBtn->setMinimumSize(QSize(80, 25));

        horizontalLayout->addWidget(tcpClientCancleBtn);


        retranslateUi(tcpclient);

        QMetaObject::connectSlotsByName(tcpclient);
    } // setupUi

    void retranslateUi(QDialog *tcpclient)
    {
        tcpclient->setWindowTitle(QCoreApplication::translate("tcpclient", "\346\216\245\346\224\266\347\253\257", nullptr));
        tcpClientStatusLabel->setText(QCoreApplication::translate("tcpclient", "\347\255\211\345\276\205\346\216\245\345\217\227\346\226\207\344\273\266...", nullptr));
        tcpClientCloseBtn->setText(QCoreApplication::translate("tcpclient", "\345\205\263\351\227\255", nullptr));
        tcpClientCancleBtn->setText(QCoreApplication::translate("tcpclient", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tcpclient: public Ui_tcpclient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCPCLIENT_H
