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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *lab_Port;
    QLineEdit *lineEdit_port;
    QPushButton *btn_Monitor;
    QLabel *lab_Video;
    QTextEdit *messAge;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(360, 329);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lab_Port = new QLabel(widget);
        lab_Port->setObjectName(QString::fromUtf8("lab_Port"));

        horizontalLayout->addWidget(lab_Port);

        lineEdit_port = new QLineEdit(widget);
        lineEdit_port->setObjectName(QString::fromUtf8("lineEdit_port"));

        horizontalLayout->addWidget(lineEdit_port);

        btn_Monitor = new QPushButton(widget);
        btn_Monitor->setObjectName(QString::fromUtf8("btn_Monitor"));

        horizontalLayout->addWidget(btn_Monitor);


        verticalLayout->addWidget(widget);

        lab_Video = new QLabel(centralwidget);
        lab_Video->setObjectName(QString::fromUtf8("lab_Video"));

        verticalLayout->addWidget(lab_Video);

        messAge = new QTextEdit(centralwidget);
        messAge->setObjectName(QString::fromUtf8("messAge"));

        verticalLayout->addWidget(messAge);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 360, 27));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        lab_Port->setText(QCoreApplication::translate("MainWindow", "\347\253\257\345\217\243\357\274\232", nullptr));
        btn_Monitor->setText(QCoreApplication::translate("MainWindow", "\347\233\221\345\220\254", nullptr));
        lab_Video->setText(QCoreApplication::translate("MainWindow", "lable", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
