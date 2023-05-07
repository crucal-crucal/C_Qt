/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actioninit;
    QAction *action_clean;
    QAction *action_insert;
    QAction *action_add;
    QAction *action_delete;
    QAction *action_select;
    QAction *action_exit;
    QAction *action_SelAll;
    QAction *action_SelNone;
    QAction *action_SelInvs;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_11;
    QSplitter *splitter;
    QToolBox *toolBox;
    QWidget *page_0;
    QVBoxLayout *verticalLayout_6;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QToolButton *tBtn_init;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *tBtn_clean;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QToolButton *tBtn_insert;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_4;
    QToolButton *tBtn_add;
    QSpacerItem *horizontalSpacer_9;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_5;
    QToolButton *tBtn_delete;
    QSpacerItem *horizontalSpacer_10;
    QWidget *page_1;
    QVBoxLayout *verticalLayout_7;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_11;
    QCheckBox *chkBoxSorting;
    QSpacerItem *horizontalSpacer_14;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_12;
    QToolButton *tBtnSortAsc;
    QSpacerItem *horizontalSpacer_15;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_13;
    QToolButton *tBtnSortDes;
    QSpacerItem *horizontalSpacer_16;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_9;
    QToolButton *tBtnClearText;
    QToolButton *tBtnAddLine;
    QPlainTextEdit *plainTextEdit;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_10;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label;
    QLineEdit *editCutItemText;
    QCheckBox *chkBoxListEditable;
    QHBoxLayout *horizontalLayout_11;
    QToolButton *tBtn_selectItem;
    QToolButton *tBtn_SelAll;
    QToolButton *tBtn_SelNone;
    QToolButton *tBtn_SelInvs;
    QListWidget *listWidget;
    QStatusBar *statusbar;
    QToolBar *maintoolBar;
    QMenuBar *menuBar;
    QMenu *menu;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(453, 389);
        MainWindow->setStyleSheet(QString::fromUtf8("QToolButton#tBtn_init,#tBtn_add,#tBtn_clean,#tBtn_delete,#tBtn_insert\n"
"{\n"
"	background-color: transparent;\n"
"	border: none;\n"
"}\n"
"\n"
"QToolButton#tBtn_init:hover,#tBtn_add:hover,#tBtn_clean:hover,#tBtn_delete:hover,\n"
"#tBtn_insert:hover\n"
"{\n"
"	background-color: rgb(229,243,255);\n"
"}"));
        actioninit = new QAction(MainWindow);
        actioninit->setObjectName("actioninit");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/128.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        actioninit->setIcon(icon);
        action_clean = new QAction(MainWindow);
        action_clean->setObjectName("action_clean");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/delete1.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        action_clean->setIcon(icon1);
        action_insert = new QAction(MainWindow);
        action_insert->setObjectName("action_insert");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/424.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        action_insert->setIcon(icon2);
        action_add = new QAction(MainWindow);
        action_add->setObjectName("action_add");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/316.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        action_add->setIcon(icon3);
        action_delete = new QAction(MainWindow);
        action_delete->setObjectName("action_delete");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/324.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        action_delete->setIcon(icon4);
        action_select = new QAction(MainWindow);
        action_select->setObjectName("action_select");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/124.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        action_select->setIcon(icon5);
        action_exit = new QAction(MainWindow);
        action_exit->setObjectName("action_exit");
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/exit.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        action_exit->setIcon(icon6);
        action_SelAll = new QAction(MainWindow);
        action_SelAll->setObjectName("action_SelAll");
        action_SelNone = new QAction(MainWindow);
        action_SelNone->setObjectName("action_SelNone");
        action_SelInvs = new QAction(MainWindow);
        action_SelInvs->setObjectName("action_SelInvs");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_11 = new QVBoxLayout(centralwidget);
        verticalLayout_11->setObjectName("verticalLayout_11");
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Horizontal);
        toolBox = new QToolBox(splitter);
        toolBox->setObjectName("toolBox");
        page_0 = new QWidget();
        page_0->setObjectName("page_0");
        page_0->setGeometry(QRect(0, 0, 179, 185));
        verticalLayout_6 = new QVBoxLayout(page_0);
        verticalLayout_6->setObjectName("verticalLayout_6");
        widget = new QWidget(page_0);
        widget->setObjectName("widget");
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        tBtn_init = new QToolButton(widget);
        tBtn_init->setObjectName("tBtn_init");
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tBtn_init->sizePolicy().hasHeightForWidth());
        tBtn_init->setSizePolicy(sizePolicy);
        tBtn_init->setMinimumSize(QSize(90, 22));
        tBtn_init->setContextMenuPolicy(Qt::DefaultContextMenu);
        tBtn_init->setStyleSheet(QString::fromUtf8(""));
        tBtn_init->setPopupMode(QToolButton::DelayedPopup);
        tBtn_init->setToolButtonStyle(Qt::ToolButtonIconOnly);
        tBtn_init->setArrowType(Qt::NoArrow);

        horizontalLayout->addWidget(tBtn_init);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        tBtn_clean = new QToolButton(widget);
        tBtn_clean->setObjectName("tBtn_clean");
        sizePolicy.setHeightForWidth(tBtn_clean->sizePolicy().hasHeightForWidth());
        tBtn_clean->setSizePolicy(sizePolicy);
        tBtn_clean->setMinimumSize(QSize(90, 22));
        tBtn_clean->setToolButtonStyle(Qt::ToolButtonIconOnly);

        horizontalLayout_2->addWidget(tBtn_clean);

        horizontalSpacer_7 = new QSpacerItem(38, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_7);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        tBtn_insert = new QToolButton(widget);
        tBtn_insert->setObjectName("tBtn_insert");
        sizePolicy.setHeightForWidth(tBtn_insert->sizePolicy().hasHeightForWidth());
        tBtn_insert->setSizePolicy(sizePolicy);
        tBtn_insert->setMinimumSize(QSize(90, 22));
        tBtn_insert->setToolButtonStyle(Qt::ToolButtonIconOnly);

        horizontalLayout_3->addWidget(tBtn_insert);

        horizontalSpacer_8 = new QSpacerItem(38, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_8);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        tBtn_add = new QToolButton(widget);
        tBtn_add->setObjectName("tBtn_add");
        tBtn_add->setMinimumSize(QSize(90, 22));
        tBtn_add->setToolButtonStyle(Qt::ToolButtonIconOnly);

        horizontalLayout_4->addWidget(tBtn_add);

        horizontalSpacer_9 = new QSpacerItem(38, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_9);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        tBtn_delete = new QToolButton(widget);
        tBtn_delete->setObjectName("tBtn_delete");
        tBtn_delete->setMinimumSize(QSize(90, 22));
        tBtn_delete->setToolButtonStyle(Qt::ToolButtonIconOnly);

        horizontalLayout_5->addWidget(tBtn_delete);

        horizontalSpacer_10 = new QSpacerItem(38, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_10);


        verticalLayout->addLayout(horizontalLayout_5);


        verticalLayout_2->addLayout(verticalLayout);


        verticalLayout_6->addWidget(widget);

        toolBox->addItem(page_0, QString::fromUtf8("\345\210\227\350\241\250\351\241\271\346\223\215\344\275\234"));
        page_1 = new QWidget();
        page_1->setObjectName("page_1");
        page_1->setGeometry(QRect(0, 0, 179, 185));
        verticalLayout_7 = new QVBoxLayout(page_1);
        verticalLayout_7->setObjectName("verticalLayout_7");
        widget_2 = new QWidget(page_1);
        widget_2->setObjectName("widget_2");
        verticalLayout_4 = new QVBoxLayout(widget_2);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_11);

        chkBoxSorting = new QCheckBox(widget_2);
        chkBoxSorting->setObjectName("chkBoxSorting");
        chkBoxSorting->setMinimumSize(QSize(50, 0));

        horizontalLayout_6->addWidget(chkBoxSorting);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_14);


        verticalLayout_3->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_12);

        tBtnSortAsc = new QToolButton(widget_2);
        tBtnSortAsc->setObjectName("tBtnSortAsc");
        tBtnSortAsc->setMinimumSize(QSize(50, 0));
        tBtnSortAsc->setArrowType(Qt::NoArrow);

        horizontalLayout_7->addWidget(tBtnSortAsc);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_15);


        verticalLayout_3->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_13);

        tBtnSortDes = new QToolButton(widget_2);
        tBtnSortDes->setObjectName("tBtnSortDes");
        tBtnSortDes->setMinimumSize(QSize(50, 0));

        horizontalLayout_8->addWidget(tBtnSortDes);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_16);


        verticalLayout_3->addLayout(horizontalLayout_8);


        verticalLayout_4->addLayout(verticalLayout_3);


        verticalLayout_7->addWidget(widget_2);

        toolBox->addItem(page_1, QString::fromUtf8("\345\210\227\350\241\250\346\216\222\345\210\227"));
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        page_2->setGeometry(QRect(0, 0, 179, 185));
        verticalLayout_8 = new QVBoxLayout(page_2);
        verticalLayout_8->setObjectName("verticalLayout_8");
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        tBtnClearText = new QToolButton(page_2);
        tBtnClearText->setObjectName("tBtnClearText");

        horizontalLayout_9->addWidget(tBtnClearText);

        tBtnAddLine = new QToolButton(page_2);
        tBtnAddLine->setObjectName("tBtnAddLine");

        horizontalLayout_9->addWidget(tBtnAddLine);


        verticalLayout_5->addLayout(horizontalLayout_9);

        plainTextEdit = new QPlainTextEdit(page_2);
        plainTextEdit->setObjectName("plainTextEdit");

        verticalLayout_5->addWidget(plainTextEdit);


        verticalLayout_8->addLayout(verticalLayout_5);

        toolBox->addItem(page_2, QString::fromUtf8("\344\277\241\345\217\267\345\217\221\345\260\204\346\227\266\346\234\272"));
        splitter->addWidget(toolBox);
        groupBox = new QGroupBox(splitter);
        groupBox->setObjectName("groupBox");
        verticalLayout_10 = new QVBoxLayout(groupBox);
        verticalLayout_10->setObjectName("verticalLayout_10");
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName("verticalLayout_9");
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        horizontalLayout_10->addWidget(label);

        editCutItemText = new QLineEdit(groupBox);
        editCutItemText->setObjectName("editCutItemText");

        horizontalLayout_10->addWidget(editCutItemText);

        chkBoxListEditable = new QCheckBox(groupBox);
        chkBoxListEditable->setObjectName("chkBoxListEditable");

        horizontalLayout_10->addWidget(chkBoxListEditable);


        verticalLayout_9->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        tBtn_selectItem = new QToolButton(groupBox);
        tBtn_selectItem->setObjectName("tBtn_selectItem");
        tBtn_selectItem->setPopupMode(QToolButton::MenuButtonPopup);

        horizontalLayout_11->addWidget(tBtn_selectItem);

        tBtn_SelAll = new QToolButton(groupBox);
        tBtn_SelAll->setObjectName("tBtn_SelAll");
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tBtn_SelAll->sizePolicy().hasHeightForWidth());
        tBtn_SelAll->setSizePolicy(sizePolicy1);
        tBtn_SelAll->setMinimumSize(QSize(10, 0));

        horizontalLayout_11->addWidget(tBtn_SelAll);

        tBtn_SelNone = new QToolButton(groupBox);
        tBtn_SelNone->setObjectName("tBtn_SelNone");
        sizePolicy1.setHeightForWidth(tBtn_SelNone->sizePolicy().hasHeightForWidth());
        tBtn_SelNone->setSizePolicy(sizePolicy1);

        horizontalLayout_11->addWidget(tBtn_SelNone);

        tBtn_SelInvs = new QToolButton(groupBox);
        tBtn_SelInvs->setObjectName("tBtn_SelInvs");
        sizePolicy1.setHeightForWidth(tBtn_SelInvs->sizePolicy().hasHeightForWidth());
        tBtn_SelInvs->setSizePolicy(sizePolicy1);

        horizontalLayout_11->addWidget(tBtn_SelInvs);


        verticalLayout_9->addLayout(horizontalLayout_11);

        listWidget = new QListWidget(groupBox);
        listWidget->setObjectName("listWidget");

        verticalLayout_9->addWidget(listWidget);


        verticalLayout_10->addLayout(verticalLayout_9);

        splitter->addWidget(groupBox);

        verticalLayout_11->addWidget(splitter);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        maintoolBar = new QToolBar(MainWindow);
        maintoolBar->setObjectName("maintoolBar");
        maintoolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        maintoolBar->setFloatable(true);
        MainWindow->addToolBar(Qt::TopToolBarArea, maintoolBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 453, 22));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(menuBar->sizePolicy().hasHeightForWidth());
        menuBar->setSizePolicy(sizePolicy2);
        menuBar->setMinimumSize(QSize(0, 0));
        menu = new QMenu(menuBar);
        menu->setObjectName("menu");
        MainWindow->setMenuBar(menuBar);

        maintoolBar->addAction(actioninit);
        maintoolBar->addAction(action_clean);
        maintoolBar->addAction(action_insert);
        maintoolBar->addAction(action_add);
        maintoolBar->addAction(action_delete);
        maintoolBar->addSeparator();
        maintoolBar->addAction(action_exit);
        menuBar->addAction(menu->menuAction());
        menu->addAction(actioninit);
        menu->addAction(action_clean);
        menu->addAction(action_insert);
        menu->addAction(action_add);
        menu->addAction(action_delete);

        retranslateUi(MainWindow);

        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actioninit->setText(QCoreApplication::translate("MainWindow", "\345\210\235\345\247\213\345\214\226\345\210\227\350\241\250", nullptr));
        action_clean->setText(QCoreApplication::translate("MainWindow", "\346\270\205\351\231\244\345\210\227\350\241\250", nullptr));
        action_insert->setText(QCoreApplication::translate("MainWindow", "\346\217\222\345\205\245\351\241\271", nullptr));
        action_add->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\351\241\271", nullptr));
        action_delete->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\345\275\223\345\211\215\351\241\271", nullptr));
        action_select->setText(QCoreApplication::translate("MainWindow", "\351\241\271\351\200\211\346\213\251", nullptr));
        action_exit->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        action_SelAll->setText(QCoreApplication::translate("MainWindow", "\345\205\250\351\200\211", nullptr));
        action_SelNone->setText(QCoreApplication::translate("MainWindow", "\347\251\272\351\200\211", nullptr));
        action_SelInvs->setText(QCoreApplication::translate("MainWindow", "\345\217\215\351\200\211", nullptr));
        tBtn_init->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        tBtn_clean->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        tBtn_insert->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        tBtn_add->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        tBtn_delete->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_0), QCoreApplication::translate("MainWindow", "\345\210\227\350\241\250\351\241\271\346\223\215\344\275\234", nullptr));
        chkBoxSorting->setText(QCoreApplication::translate("MainWindow", "\345\205\201\350\256\270\346\216\222\345\272\217", nullptr));
        tBtnSortAsc->setText(QCoreApplication::translate("MainWindow", "\345\215\207\345\272\217\346\216\222\345\272\217", nullptr));
        tBtnSortDes->setText(QCoreApplication::translate("MainWindow", "\351\231\215\345\272\217\346\216\222\345\272\217", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_1), QCoreApplication::translate("MainWindow", "\345\210\227\350\241\250\346\216\222\345\210\227", nullptr));
        tBtnClearText->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272\346\226\207\346\234\254", nullptr));
        tBtnAddLine->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\347\251\272\350\241\214", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_2), QCoreApplication::translate("MainWindow", "\344\277\241\345\217\267\345\217\221\345\260\204\346\227\266\346\234\272", nullptr));
        groupBox->setTitle(QString());
        label->setText(QCoreApplication::translate("MainWindow", "\345\275\223\345\211\215\351\241\271\345\217\230\345\214\226", nullptr));
        chkBoxListEditable->setText(QCoreApplication::translate("MainWindow", "\351\241\271\345\217\257\347\274\226\350\276\221\347\232\204", nullptr));
        tBtn_selectItem->setText(QCoreApplication::translate("MainWindow", "\351\241\271\351\200\211\346\213\251", nullptr));
        tBtn_SelAll->setText(QCoreApplication::translate("MainWindow", "\345\205\250\351\200\211", nullptr));
        tBtn_SelNone->setText(QCoreApplication::translate("MainWindow", "\347\251\272\351\200\211", nullptr));
        tBtn_SelInvs->setText(QCoreApplication::translate("MainWindow", "\345\217\215\351\200\211", nullptr));
        maintoolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\345\210\235\345\247\213\345\214\226", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
