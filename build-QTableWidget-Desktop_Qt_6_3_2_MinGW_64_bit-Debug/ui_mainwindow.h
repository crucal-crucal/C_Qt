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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_3;
    QSplitter *splitter_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QPushButton *btnSetHeader;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnSetRows;
    QSpinBox *spinRowCount;
    QPushButton *btnIniData;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnInsertRow;
    QPushButton *btnAppendRow;
    QPushButton *btnDelCurRow;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnAutoHeght;
    QPushButton *btnAutoWidth;
    QPushButton *btnReadToEdit;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *chkBoxTabEditable;
    QCheckBox *chkBoxRowColor;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *chkBoxHeaderH;
    QCheckBox *chkBoxHeaderV;
    QHBoxLayout *horizontalLayout_6;
    QRadioButton *rBtnSelectRow;
    QRadioButton *rBtnSelectItem;
    QSplitter *splitter;
    QTableWidget *tableInfo;
    QPlainTextEdit *plainTextEdit;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(756, 354);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        splitter_2 = new QSplitter(centralwidget);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        groupBox = new QGroupBox(splitter_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        btnSetHeader = new QPushButton(groupBox);
        btnSetHeader->setObjectName(QString::fromUtf8("btnSetHeader"));

        verticalLayout->addWidget(btnSetHeader);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnSetRows = new QPushButton(groupBox);
        btnSetRows->setObjectName(QString::fromUtf8("btnSetRows"));

        horizontalLayout->addWidget(btnSetRows);

        spinRowCount = new QSpinBox(groupBox);
        spinRowCount->setObjectName(QString::fromUtf8("spinRowCount"));

        horizontalLayout->addWidget(spinRowCount);


        verticalLayout->addLayout(horizontalLayout);

        btnIniData = new QPushButton(groupBox);
        btnIniData->setObjectName(QString::fromUtf8("btnIniData"));

        verticalLayout->addWidget(btnIniData);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        btnInsertRow = new QPushButton(groupBox);
        btnInsertRow->setObjectName(QString::fromUtf8("btnInsertRow"));

        horizontalLayout_2->addWidget(btnInsertRow);

        btnAppendRow = new QPushButton(groupBox);
        btnAppendRow->setObjectName(QString::fromUtf8("btnAppendRow"));

        horizontalLayout_2->addWidget(btnAppendRow);


        verticalLayout->addLayout(horizontalLayout_2);

        btnDelCurRow = new QPushButton(groupBox);
        btnDelCurRow->setObjectName(QString::fromUtf8("btnDelCurRow"));

        verticalLayout->addWidget(btnDelCurRow);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        btnAutoHeght = new QPushButton(groupBox);
        btnAutoHeght->setObjectName(QString::fromUtf8("btnAutoHeght"));

        horizontalLayout_3->addWidget(btnAutoHeght);

        btnAutoWidth = new QPushButton(groupBox);
        btnAutoWidth->setObjectName(QString::fromUtf8("btnAutoWidth"));

        horizontalLayout_3->addWidget(btnAutoWidth);


        verticalLayout->addLayout(horizontalLayout_3);

        btnReadToEdit = new QPushButton(groupBox);
        btnReadToEdit->setObjectName(QString::fromUtf8("btnReadToEdit"));

        verticalLayout->addWidget(btnReadToEdit);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        chkBoxTabEditable = new QCheckBox(groupBox);
        chkBoxTabEditable->setObjectName(QString::fromUtf8("chkBoxTabEditable"));
        chkBoxTabEditable->setCheckable(true);
        chkBoxTabEditable->setChecked(false);

        horizontalLayout_4->addWidget(chkBoxTabEditable);

        chkBoxRowColor = new QCheckBox(groupBox);
        chkBoxRowColor->setObjectName(QString::fromUtf8("chkBoxRowColor"));
        chkBoxRowColor->setChecked(false);

        horizontalLayout_4->addWidget(chkBoxRowColor);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        chkBoxHeaderH = new QCheckBox(groupBox);
        chkBoxHeaderH->setObjectName(QString::fromUtf8("chkBoxHeaderH"));

        horizontalLayout_5->addWidget(chkBoxHeaderH);

        chkBoxHeaderV = new QCheckBox(groupBox);
        chkBoxHeaderV->setObjectName(QString::fromUtf8("chkBoxHeaderV"));

        horizontalLayout_5->addWidget(chkBoxHeaderV);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        rBtnSelectRow = new QRadioButton(groupBox);
        rBtnSelectRow->setObjectName(QString::fromUtf8("rBtnSelectRow"));

        horizontalLayout_6->addWidget(rBtnSelectRow);

        rBtnSelectItem = new QRadioButton(groupBox);
        rBtnSelectItem->setObjectName(QString::fromUtf8("rBtnSelectItem"));

        horizontalLayout_6->addWidget(rBtnSelectItem);


        verticalLayout->addLayout(horizontalLayout_6);


        verticalLayout_2->addLayout(verticalLayout);

        splitter_2->addWidget(groupBox);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        tableInfo = new QTableWidget(splitter);
        tableInfo->setObjectName(QString::fromUtf8("tableInfo"));
        splitter->addWidget(tableInfo);
        plainTextEdit = new QPlainTextEdit(splitter);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        splitter->addWidget(plainTextEdit);
        splitter_2->addWidget(splitter);

        verticalLayout_3->addWidget(splitter_2);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QString());
        btnSetHeader->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256\346\260\264\345\271\263\350\241\250\345\244\264", nullptr));
        btnSetRows->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256\350\241\214\346\225\260", nullptr));
        btnIniData->setText(QCoreApplication::translate("MainWindow", "\345\210\235\345\247\213\345\214\226\350\241\250\346\240\274\346\225\260\346\215\256", nullptr));
        btnInsertRow->setText(QCoreApplication::translate("MainWindow", "\346\217\222\345\205\245\350\241\214", nullptr));
        btnAppendRow->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\350\241\214", nullptr));
        btnDelCurRow->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\345\275\223\345\211\215\350\241\214", nullptr));
        btnAutoHeght->setText(QCoreApplication::translate("MainWindow", "\350\207\252\345\212\250\350\260\203\350\212\202\350\241\214\351\253\230", nullptr));
        btnAutoWidth->setText(QCoreApplication::translate("MainWindow", "\350\207\252\345\212\250\350\260\203\350\212\202\345\210\227\345\256\275", nullptr));
        btnReadToEdit->setText(QCoreApplication::translate("MainWindow", "\350\257\273\345\217\226\350\241\250\346\240\274\345\206\205\345\256\271\345\210\260\346\226\207\346\234\254", nullptr));
        chkBoxTabEditable->setText(QCoreApplication::translate("MainWindow", "\350\241\250\346\240\274\345\217\257\347\274\226\350\276\221", nullptr));
        chkBoxRowColor->setText(QCoreApplication::translate("MainWindow", "\351\227\264\351\232\224\350\241\214\345\272\225\350\211\262", nullptr));
        chkBoxHeaderH->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\346\260\264\345\271\263\350\241\250\345\244\264", nullptr));
        chkBoxHeaderV->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\345\236\202\347\233\264\350\241\250\345\244\264", nullptr));
        rBtnSelectRow->setText(QCoreApplication::translate("MainWindow", "\350\241\214\351\200\211\346\213\251", nullptr));
        rBtnSelectItem->setText(QCoreApplication::translate("MainWindow", "\345\215\225\345\205\203\346\240\274\351\200\211\346\213\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
