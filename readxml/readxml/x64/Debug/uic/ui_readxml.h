/********************************************************************************
** Form generated from reading UI file 'readxml.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_READXML_H
#define UI_READXML_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_readxmlClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QPlainTextEdit *plainTextEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *readxmlClass)
    {
        if (readxmlClass->objectName().isEmpty())
            readxmlClass->setObjectName(QStringLiteral("readxmlClass"));
        readxmlClass->resize(600, 400);
        centralWidget = new QWidget(readxmlClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        plainTextEdit = new QPlainTextEdit(centralWidget);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));

        gridLayout->addWidget(plainTextEdit, 0, 0, 1, 1);

        readxmlClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(readxmlClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 26));
        readxmlClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(readxmlClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        readxmlClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(readxmlClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        readxmlClass->setStatusBar(statusBar);

        retranslateUi(readxmlClass);

        QMetaObject::connectSlotsByName(readxmlClass);
    } // setupUi

    void retranslateUi(QMainWindow *readxmlClass)
    {
        readxmlClass->setWindowTitle(QApplication::translate("readxmlClass", "readxml", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class readxmlClass: public Ui_readxmlClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_READXML_H
