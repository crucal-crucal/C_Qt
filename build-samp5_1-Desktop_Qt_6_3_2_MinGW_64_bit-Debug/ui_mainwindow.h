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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_4;
    QSplitter *splitter;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout;
    QPushButton *btnIniList;
    QPushButton *btnListAppend;
    QPushButton *btnListInsert;
    QPushButton *btnListDelete;
    QPushButton *btnListMoveUp;
    QPushButton *btnListMoveDown;
    QPushButton *btnListSort;
    QPushButton *btnListClear;
    QCheckBox *chkEditable;
    QListView *listView;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QPushButton *btnTextClear;
    QPushButton *btnTextImport;
    QPlainTextEdit *plainTextEdit;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(580, 368);
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\256\213\344\275\223")});
        font.setPointSize(10);
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_4 = new QVBoxLayout(centralwidget);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(5, 5, 5, 5);
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        groupBox = new QGroupBox(splitter);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setSpacing(3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(4, 4, 4, 4);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        btnIniList = new QPushButton(groupBox);
        btnIniList->setObjectName(QString::fromUtf8("btnIniList"));

        gridLayout->addWidget(btnIniList, 0, 0, 1, 1);

        btnListAppend = new QPushButton(groupBox);
        btnListAppend->setObjectName(QString::fromUtf8("btnListAppend"));

        gridLayout->addWidget(btnListAppend, 1, 0, 1, 1);

        btnListInsert = new QPushButton(groupBox);
        btnListInsert->setObjectName(QString::fromUtf8("btnListInsert"));

        gridLayout->addWidget(btnListInsert, 1, 1, 1, 1);

        btnListDelete = new QPushButton(groupBox);
        btnListDelete->setObjectName(QString::fromUtf8("btnListDelete"));

        gridLayout->addWidget(btnListDelete, 1, 2, 1, 1);

        btnListMoveUp = new QPushButton(groupBox);
        btnListMoveUp->setObjectName(QString::fromUtf8("btnListMoveUp"));

        gridLayout->addWidget(btnListMoveUp, 2, 0, 1, 1);

        btnListMoveDown = new QPushButton(groupBox);
        btnListMoveDown->setObjectName(QString::fromUtf8("btnListMoveDown"));

        gridLayout->addWidget(btnListMoveDown, 2, 1, 1, 1);

        btnListSort = new QPushButton(groupBox);
        btnListSort->setObjectName(QString::fromUtf8("btnListSort"));
        btnListSort->setCheckable(true);

        gridLayout->addWidget(btnListSort, 2, 2, 1, 1);

        btnListClear = new QPushButton(groupBox);
        btnListClear->setObjectName(QString::fromUtf8("btnListClear"));

        gridLayout->addWidget(btnListClear, 0, 1, 1, 1);

        chkEditable = new QCheckBox(groupBox);
        chkEditable->setObjectName(QString::fromUtf8("chkEditable"));
        chkEditable->setChecked(true);

        gridLayout->addWidget(chkEditable, 0, 2, 1, 1);


        verticalLayout_3->addLayout(gridLayout);

        listView = new QListView(groupBox);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setAlternatingRowColors(true);

        verticalLayout_3->addWidget(listView);

        splitter->addWidget(groupBox);
        groupBox_2 = new QGroupBox(splitter);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setSpacing(3);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(4, 4, 4, 4);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        btnTextClear = new QPushButton(groupBox_2);
        btnTextClear->setObjectName(QString::fromUtf8("btnTextClear"));

        verticalLayout->addWidget(btnTextClear);

        btnTextImport = new QPushButton(groupBox_2);
        btnTextImport->setObjectName(QString::fromUtf8("btnTextImport"));

        verticalLayout->addWidget(btnTextImport);


        verticalLayout_2->addLayout(verticalLayout);

        plainTextEdit = new QPlainTextEdit(groupBox_2);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));

        verticalLayout_2->addWidget(plainTextEdit);

        splitter->addWidget(groupBox_2);

        verticalLayout_4->addWidget(splitter);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "QStringListModel\345\222\214QListView", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "ListView", nullptr));
        btnIniList->setText(QCoreApplication::translate("MainWindow", "\346\201\242\345\244\215\345\210\227\350\241\250", nullptr));
        btnListAppend->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\351\241\271", nullptr));
        btnListInsert->setText(QCoreApplication::translate("MainWindow", "\346\217\222\345\205\245\351\241\271", nullptr));
        btnListDelete->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\351\241\271", nullptr));
        btnListMoveUp->setText(QCoreApplication::translate("MainWindow", "\344\270\212\347\247\273", nullptr));
        btnListMoveDown->setText(QCoreApplication::translate("MainWindow", "\344\270\213\347\247\273", nullptr));
        btnListSort->setText(QCoreApplication::translate("MainWindow", "\346\216\222\345\272\217", nullptr));
        btnListClear->setText(QCoreApplication::translate("MainWindow", "\346\270\205\351\231\244\345\210\227\350\241\250", nullptr));
        chkEditable->setText(QCoreApplication::translate("MainWindow", "\345\205\201\350\256\270\347\274\226\350\276\221", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "PlainTextEdit", nullptr));
        btnTextClear->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272\346\226\207\346\234\254", nullptr));
        btnTextImport->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\346\225\260\346\215\256\346\250\241\345\236\213\347\232\204StringList", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
