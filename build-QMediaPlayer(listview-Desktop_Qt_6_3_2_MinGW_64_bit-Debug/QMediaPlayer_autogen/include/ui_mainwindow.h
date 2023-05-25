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
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "videowidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionvideo;
    QAction *actionplainTextEdit;
    QAction *actionlabel;
    QAction *action_add;
    QAction *action_remove;
    QAction *action_clear;
    QAction *action_exit;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *lineEdit;
    QPushButton *Btn_Serch;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QListView *listView;
    videowidget *m_widget;
    QPlainTextEdit *plainTextEdit;
    QHBoxLayout *horizontalLayout;
    QToolButton *tbtn_play;
    QToolButton *tbtn_pause;
    QToolButton *tbtn_stop;
    QToolButton *tbtn_next;
    QToolButton *tbtn_last;
    QDoubleSpinBox *doubleSpinBox;
    QPushButton *btn_cycle;
    QToolButton *tbtn_mute;
    QSlider *hSlider_sound;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_name;
    QSlider *hSlider_progress;
    QLabel *label_played;
    QLabel *label_time;
    QLabel *lab_pixmap;
    QStatusBar *statusbar;
    QMenuBar *menuBar;
    QMenu *menuvideo;
    QMenu *menu;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(848, 582);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow{\n"
"	border:3px solid red;\n"
"	border-radius:10px;\n"
"	background-color:pink;\n"
"	color:pink;\n"
"}\n"
"QToolButton{\n"
"	border-radius:10px;\n"
"	background-color:pink;\n"
"}\n"
"QToolButton:hover{\n"
"	border-radius:10px;\n"
"	font-size:17px;\n"
"	background-color:purple;\n"
"	color:yellow;\n"
"}"));
        actionvideo = new QAction(MainWindow);
        actionvideo->setObjectName(QString::fromUtf8("actionvideo"));
        actionvideo->setCheckable(true);
        actionplainTextEdit = new QAction(MainWindow);
        actionplainTextEdit->setObjectName(QString::fromUtf8("actionplainTextEdit"));
        actionplainTextEdit->setCheckable(true);
        actionlabel = new QAction(MainWindow);
        actionlabel->setObjectName(QString::fromUtf8("actionlabel"));
        actionlabel->setCheckable(true);
        action_add = new QAction(MainWindow);
        action_add->setObjectName(QString::fromUtf8("action_add"));
        action_remove = new QAction(MainWindow);
        action_remove->setObjectName(QString::fromUtf8("action_remove"));
        action_clear = new QAction(MainWindow);
        action_clear->setObjectName(QString::fromUtf8("action_clear"));
        action_exit = new QAction(MainWindow);
        action_exit->setObjectName(QString::fromUtf8("action_exit"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout_4->addWidget(lineEdit);

        Btn_Serch = new QPushButton(centralwidget);
        Btn_Serch->setObjectName(QString::fromUtf8("Btn_Serch"));

        horizontalLayout_4->addWidget(Btn_Serch);


        verticalLayout_2->addLayout(horizontalLayout_4);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        listView = new QListView(centralwidget);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setMinimumSize(QSize(171, 192));

        horizontalLayout_3->addWidget(listView);

        m_widget = new videowidget(centralwidget);
        m_widget->setObjectName(QString::fromUtf8("m_widget"));
        m_widget->setMinimumSize(QSize(141, 192));

        horizontalLayout_3->addWidget(m_widget);

        plainTextEdit = new QPlainTextEdit(centralwidget);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setMinimumSize(QSize(111, 191));

        horizontalLayout_3->addWidget(plainTextEdit);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tbtn_play = new QToolButton(centralwidget);
        tbtn_play->setObjectName(QString::fromUtf8("tbtn_play"));

        horizontalLayout->addWidget(tbtn_play);

        tbtn_pause = new QToolButton(centralwidget);
        tbtn_pause->setObjectName(QString::fromUtf8("tbtn_pause"));

        horizontalLayout->addWidget(tbtn_pause);

        tbtn_stop = new QToolButton(centralwidget);
        tbtn_stop->setObjectName(QString::fromUtf8("tbtn_stop"));

        horizontalLayout->addWidget(tbtn_stop);

        tbtn_next = new QToolButton(centralwidget);
        tbtn_next->setObjectName(QString::fromUtf8("tbtn_next"));

        horizontalLayout->addWidget(tbtn_next);

        tbtn_last = new QToolButton(centralwidget);
        tbtn_last->setObjectName(QString::fromUtf8("tbtn_last"));

        horizontalLayout->addWidget(tbtn_last);

        doubleSpinBox = new QDoubleSpinBox(centralwidget);
        doubleSpinBox->setObjectName(QString::fromUtf8("doubleSpinBox"));
        doubleSpinBox->setStyleSheet(QString::fromUtf8(""));
        doubleSpinBox->setDecimals(1);
        doubleSpinBox->setSingleStep(0.100000000000000);
        doubleSpinBox->setValue(1.000000000000000);

        horizontalLayout->addWidget(doubleSpinBox);

        btn_cycle = new QPushButton(centralwidget);
        btn_cycle->setObjectName(QString::fromUtf8("btn_cycle"));
        btn_cycle->setCheckable(true);
        btn_cycle->setChecked(false);

        horizontalLayout->addWidget(btn_cycle);

        tbtn_mute = new QToolButton(centralwidget);
        tbtn_mute->setObjectName(QString::fromUtf8("tbtn_mute"));

        horizontalLayout->addWidget(tbtn_mute);

        hSlider_sound = new QSlider(centralwidget);
        hSlider_sound->setObjectName(QString::fromUtf8("hSlider_sound"));
        hSlider_sound->setValue(30);
        hSlider_sound->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(hSlider_sound);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_name = new QLabel(centralwidget);
        label_name->setObjectName(QString::fromUtf8("label_name"));

        horizontalLayout_2->addWidget(label_name);

        hSlider_progress = new QSlider(centralwidget);
        hSlider_progress->setObjectName(QString::fromUtf8("hSlider_progress"));
        hSlider_progress->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(hSlider_progress);

        label_played = new QLabel(centralwidget);
        label_played->setObjectName(QString::fromUtf8("label_played"));

        horizontalLayout_2->addWidget(label_played);

        label_time = new QLabel(centralwidget);
        label_time->setObjectName(QString::fromUtf8("label_time"));

        horizontalLayout_2->addWidget(label_time);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 2, 2);

        lab_pixmap = new QLabel(centralwidget);
        lab_pixmap->setObjectName(QString::fromUtf8("lab_pixmap"));
        lab_pixmap->setMinimumSize(QSize(141, 191));

        gridLayout->addWidget(lab_pixmap, 1, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 848, 21));
        menuvideo = new QMenu(menuBar);
        menuvideo->setObjectName(QString::fromUtf8("menuvideo"));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menuBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menuBar->addAction(menuvideo->menuAction());
        menuBar->addAction(menu->menuAction());
        menuvideo->addAction(actionvideo);
        menuvideo->addAction(actionplainTextEdit);
        menuvideo->addAction(actionlabel);
        menu->addAction(action_add);
        menu->addAction(action_remove);
        menu->addAction(action_clear);
        menu->addAction(action_exit);
        toolBar->addAction(actionvideo);
        toolBar->addAction(actionplainTextEdit);
        toolBar->addAction(actionlabel);
        toolBar->addSeparator();
        toolBar->addAction(action_add);
        toolBar->addAction(action_remove);
        toolBar->addAction(action_clear);
        toolBar->addSeparator();
        toolBar->addAction(action_exit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionvideo->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\350\247\206\351\242\221\347\252\227\345\217\243", nullptr));
        actionplainTextEdit->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\346\226\207\346\234\254\347\252\227\345\217\243", nullptr));
        actionlabel->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\345\233\276\347\211\207\347\252\227\345\217\243", nullptr));
        action_add->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240", nullptr));
        action_remove->setText(QCoreApplication::translate("MainWindow", "\347\247\273\345\207\272", nullptr));
        action_clear->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272", nullptr));
        action_exit->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        Btn_Serch->setText(QCoreApplication::translate("MainWindow", "Serch", nullptr));
        tbtn_play->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213", nullptr));
        tbtn_pause->setText(QCoreApplication::translate("MainWindow", "\346\232\202\345\201\234", nullptr));
        tbtn_stop->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242", nullptr));
        tbtn_next->setText(QCoreApplication::translate("MainWindow", "\344\270\213\344\270\200\351\246\226", nullptr));
        tbtn_last->setText(QCoreApplication::translate("MainWindow", "\344\270\212\344\270\200\351\246\226", nullptr));
        doubleSpinBox->setSpecialValueText(QString());
        doubleSpinBox->setPrefix(QString());
        doubleSpinBox->setSuffix(QCoreApplication::translate("MainWindow", "\345\200\215\351\200\237", nullptr));
        btn_cycle->setText(QCoreApplication::translate("MainWindow", "\345\276\252\347\216\257\346\222\255\346\224\276", nullptr));
        tbtn_mute->setText(QCoreApplication::translate("MainWindow", "\345\243\260\351\237\263", nullptr));
        label_name->setText(QCoreApplication::translate("MainWindow", "\346\233\262\347\233\256", nullptr));
        label_played->setText(QCoreApplication::translate("MainWindow", "\345\267\262\346\222\255\346\224\276/", nullptr));
        label_time->setText(QCoreApplication::translate("MainWindow", "\346\200\273\346\227\266\351\225\277", nullptr));
        lab_pixmap->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        menuvideo->setTitle(QCoreApplication::translate("MainWindow", "video", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266\346\223\215\344\275\234", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
