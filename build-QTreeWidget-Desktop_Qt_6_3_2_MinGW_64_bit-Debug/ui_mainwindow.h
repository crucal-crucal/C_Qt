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
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actZoomFitH;
    QAction *actZoomFitW;
    QAction *actZoomIn;
    QAction *actZoomOut;
    QAction *actZoomRealSize;
    QAction *actAddFolder;
    QAction *actAddFiles;
    QAction *actDeleteItem;
    QAction *actScanItems;
    QAction *actDockVisible;
    QAction *actDockFloat;
    QAction *exit;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labPic;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QStatusBar *statusbar;
    QToolBar *toolBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QHBoxLayout *horizontalLayout;
    QTreeWidget *treeFiles;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(788, 523);
        actZoomFitH = new QAction(MainWindow);
        actZoomFitH->setObjectName(QString::fromUtf8("actZoomFitH"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/101.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        actZoomFitH->setIcon(icon);
        actZoomFitW = new QAction(MainWindow);
        actZoomFitW->setObjectName(QString::fromUtf8("actZoomFitW"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/102.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        actZoomFitW->setIcon(icon1);
        actZoomIn = new QAction(MainWindow);
        actZoomIn->setObjectName(QString::fromUtf8("actZoomIn"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/300.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        actZoomIn->setIcon(icon2);
        actZoomOut = new QAction(MainWindow);
        actZoomOut->setObjectName(QString::fromUtf8("actZoomOut"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/301.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        actZoomOut->setIcon(icon3);
        actZoomRealSize = new QAction(MainWindow);
        actZoomRealSize->setObjectName(QString::fromUtf8("actZoomRealSize"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/127.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        actZoomRealSize->setIcon(icon4);
        actAddFolder = new QAction(MainWindow);
        actAddFolder->setObjectName(QString::fromUtf8("actAddFolder"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/upfold1.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        actAddFolder->setIcon(icon5);
        actAddFiles = new QAction(MainWindow);
        actAddFiles->setObjectName(QString::fromUtf8("actAddFiles"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/images/120.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        actAddFiles->setIcon(icon6);
        actDeleteItem = new QAction(MainWindow);
        actDeleteItem->setObjectName(QString::fromUtf8("actDeleteItem"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/images/delete1.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        actDeleteItem->setIcon(icon7);
        actScanItems = new QAction(MainWindow);
        actScanItems->setObjectName(QString::fromUtf8("actScanItems"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/images/folder1.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        actScanItems->setIcon(icon8);
        actDockVisible = new QAction(MainWindow);
        actDockVisible->setObjectName(QString::fromUtf8("actDockVisible"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/images/103.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        actDockVisible->setIcon(icon9);
        actDockFloat = new QAction(MainWindow);
        actDockFloat->setObjectName(QString::fromUtf8("actDockFloat"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/images/104.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        actDockFloat->setIcon(icon10);
        exit = new QAction(MainWindow);
        exit->setObjectName(QString::fromUtf8("exit"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/images/exit.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        exit->setIcon(icon11);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 448, 407));
        horizontalLayout_2 = new QHBoxLayout(scrollAreaWidgetContents);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        labPic = new QLabel(scrollAreaWidgetContents);
        labPic->setObjectName(QString::fromUtf8("labPic"));

        horizontalLayout_2->addWidget(labPic);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 788, 22));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setSizeGripEnabled(true);
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        dockWidget->setFloating(false);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        horizontalLayout = new QHBoxLayout(dockWidgetContents);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        treeFiles = new QTreeWidget(dockWidgetContents);
        treeFiles->setObjectName(QString::fromUtf8("treeFiles"));

        horizontalLayout->addWidget(treeFiles);

        dockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menu->addAction(actAddFiles);
        menu->addAction(actDeleteItem);
        menu->addAction(actAddFolder);
        menu->addAction(actScanItems);
        menu->addSeparator();
        menu_2->addAction(actZoomFitH);
        menu_2->addAction(actZoomIn);
        menu_2->addAction(actZoomFitW);
        menu_2->addAction(actZoomOut);
        menu_2->addAction(actZoomRealSize);
        toolBar->addAction(actAddFolder);
        toolBar->addAction(actAddFiles);
        toolBar->addAction(actDeleteItem);
        toolBar->addAction(actScanItems);
        toolBar->addSeparator();
        toolBar->addAction(actZoomFitH);
        toolBar->addAction(actZoomFitW);
        toolBar->addAction(actZoomRealSize);
        toolBar->addAction(actZoomIn);
        toolBar->addAction(actZoomOut);
        toolBar->addSeparator();
        toolBar->addAction(actDockFloat);
        toolBar->addAction(actDockVisible);
        toolBar->addSeparator();
        toolBar->addAction(exit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actZoomFitH->setText(QCoreApplication::translate("MainWindow", "\351\200\202\345\220\210\351\253\230\345\272\246", nullptr));
        actZoomFitW->setText(QCoreApplication::translate("MainWindow", "\351\200\202\345\220\210\345\256\275\345\272\246", nullptr));
        actZoomIn->setText(QCoreApplication::translate("MainWindow", "\346\224\276\345\244\247\346\230\276\347\244\272", nullptr));
        actZoomOut->setText(QCoreApplication::translate("MainWindow", "\347\274\251\345\260\217\346\230\276\347\244\272", nullptr));
        actZoomRealSize->setText(QCoreApplication::translate("MainWindow", "\345\256\236\351\231\205\345\244\247\345\260\217", nullptr));
        actAddFolder->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\347\233\256\345\275\225", nullptr));
        actAddFiles->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\346\226\207\344\273\266", nullptr));
        actDeleteItem->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\350\212\202\347\202\271", nullptr));
        actScanItems->setText(QCoreApplication::translate("MainWindow", "\351\201\215\345\216\206\350\212\202\347\202\271", nullptr));
        actDockVisible->setText(QCoreApplication::translate("MainWindow", "\347\252\227\345\217\243\345\217\257\350\247\201", nullptr));
        actDockFloat->setText(QCoreApplication::translate("MainWindow", "\347\252\227\345\217\243\346\265\256\345\212\250", nullptr));
        exit->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        labPic->setText(QString());
        menu->setTitle(QCoreApplication::translate("MainWindow", "\347\233\256\345\275\225\346\240\221", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\350\247\206\345\233\276", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
