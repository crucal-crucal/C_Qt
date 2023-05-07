/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "menubutton.h"

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QStackedWidget *stackedWidget;
    QWidget *page;
    QTextBrowser *messageBrowser;
    QTextEdit *messageTextEdit;
    QPushButton *sendButton;
    QPushButton *exitButton;
    QFrame *line;
    QFrame *line_2;
    QFontComboBox *fontComboBox;
    QComboBox *sizeComboBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QToolButton *boldToolButton;
    QToolButton *italicToolButton;
    QToolButton *underlineToolButton;
    QToolButton *colorToolButton;
    QToolButton *sendToolButton;
    QToolButton *saveToolButton;
    QToolButton *clearToolButton;
    QFrame *line_3;
    QToolButton *toolButton_8;
    QLabel *label;
    QLabel *label_2;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *toolButton;
    QToolButton *toolButton_2;
    QToolButton *toolButton_3;
    QToolButton *toolButton_4;
    QToolButton *toolButton_5;
    QToolButton *toolButton_6;
    QToolButton *toolButton_7;
    QPushButton *pushButton;
    QLabel *userNumLabel;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_3;
    MenuButton *menuButton;
    QToolButton *minButton;
    QToolButton *maxButton;
    QToolButton *closeButton;
    QTableWidget *userTableWidget;
    QWidget *page_2;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(750, 500);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Widget->sizePolicy().hasHeightForWidth());
        Widget->setSizePolicy(sizePolicy);
        Widget->setMinimumSize(QSize(750, 500));
        Widget->setMaximumSize(QSize(750, 500));
        Widget->setAutoFillBackground(false);
        Widget->setStyleSheet(QString::fromUtf8(""));
        stackedWidget = new QStackedWidget(Widget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(5, 5, 740, 490));
        stackedWidget->setMinimumSize(QSize(740, 490));
        stackedWidget->setMaximumSize(QSize(740, 490));
        stackedWidget->setStyleSheet(QString::fromUtf8("QStackedWidget {background-image: url(:/images/background.jpg);}\n"
""));
        stackedWidget->setFrameShape(QFrame::NoFrame);
        stackedWidget->setFrameShadow(QFrame::Sunken);
        stackedWidget->setLineWidth(1);
        stackedWidget->setMidLineWidth(0);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        messageBrowser = new QTextBrowser(page);
        messageBrowser->setObjectName(QString::fromUtf8("messageBrowser"));
        messageBrowser->setGeometry(QRect(0, 90, 480, 250));
        messageBrowser->setMinimumSize(QSize(480, 250));
        messageBrowser->setMaximumSize(QSize(480, 250));
        QFont font;
        font.setPointSize(12);
        messageBrowser->setFont(font);
        messageBrowser->setStyleSheet(QString::fromUtf8("QTextBrowser { background-color: rgb(255, 255, 255,0); border-radius: 3px; color: rgb(0, 0, 0); }"));
        messageBrowser->setLineWidth(1);
        //messageBrowser->setTabStopWidth(80);
        messageBrowser->setCursorWidth(1);
        messageTextEdit = new QTextEdit(page);
        messageTextEdit->setObjectName(QString::fromUtf8("messageTextEdit"));
        messageTextEdit->setGeometry(QRect(10, 390, 480, 70));
        messageTextEdit->setMinimumSize(QSize(480, 70));
        messageTextEdit->setMaximumSize(QSize(16777215, 16777215));
        messageTextEdit->setFont(font);
        messageTextEdit->setStyleSheet(QString::fromUtf8("QTextEdit { background-color: rgb(255, 255, 255,0); border-radius: 3px;color: rgb(0, 0, 0);  }\n"
"\n"
"\n"
""));
        messageTextEdit->setLineWidth(1);
        sendButton = new QPushButton(page);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sendButton->setGeometry(QRect(400, 462, 60, 25));
        sendButton->setMinimumSize(QSize(60, 25));
        sendButton->setMaximumSize(QSize(103, 41));
        sendButton->setStyleSheet(QString::fromUtf8("QPushButton { background-color: rgb(50, 50, 50,200); border-radius: 3px; color: rgb(255, 255, 255); }\n"
" QPushButton:hover { background-color: rgb(50, 50, 50,255);}\n"
""));
        exitButton = new QPushButton(page);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        exitButton->setGeometry(QRect(330, 462, 60, 25));
        exitButton->setMinimumSize(QSize(60, 25));
        exitButton->setMaximumSize(QSize(103, 41));
        exitButton->setStyleSheet(QString::fromUtf8("QPushButton { background-color: rgb(50, 50, 50,200); border-radius: 3px; color: rgb(255, 255, 255); }\n"
" QPushButton:hover { background-color: rgb(50, 50, 50,255);}\n"
""));
        line = new QFrame(page);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(10, 347, 480, 2));
        line->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 125);"));
        line->setFrameShadow(QFrame::Sunken);
        line->setLineWidth(1);
        line->setFrameShape(QFrame::HLine);
        line_2 = new QFrame(page);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(490, 80, 2, 415));
        line_2->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 125);"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        fontComboBox = new QFontComboBox(page);
        fontComboBox->setObjectName(QString::fromUtf8("fontComboBox"));
        fontComboBox->setEnabled(true);
        fontComboBox->setGeometry(QRect(10, 350, 155, 30));
        fontComboBox->setMinimumSize(QSize(155, 30));
        fontComboBox->setMaximumSize(QSize(155, 30));
        fontComboBox->setFont(font);
        fontComboBox->setMouseTracking(false);
        fontComboBox->setAcceptDrops(false);
        fontComboBox->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"	background-color: rgb(255, 255, 255);\n"
"    border: 1px solid gray;\n"
"    border-radius: 3px;\n"
"    padding: 1px 2px 1px 2px;  /*\351\222\210\345\257\271\344\272\216\347\273\204\345\220\210\346\241\206\344\270\255\347\232\204\346\226\207\346\234\254\345\206\205\345\256\271*/\n"
"    /*min-width: 9em;   \347\273\204\345\220\210\346\241\206\347\232\204\346\234\200\345\260\217\345\256\275\345\272\246*/\n"
"}\n"
"QComboBox::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
"    width: 20px;\n"
"\n"
"    border-left-width: 1px;\n"
"    border-left-color: darkgray;\n"
"    border-left-style: solid; \n"
"    border-top-right-radius: 3px; \n"
"    border-bottom-right-radius: 3px;\n"
"}\n"
"QComboBox::down-arrow {\n"
"    image: url(:/images/QComboBox);\n"
"}\n"
"QComboBox::drop-down:hover { background-color: rgb(50, 50, 50,255);}"));
        fontComboBox->setEditable(false);
        sizeComboBox = new QComboBox(page);
        sizeComboBox->addItem(QString());
        sizeComboBox->addItem(QString());
        sizeComboBox->addItem(QString());
        sizeComboBox->addItem(QString());
        sizeComboBox->addItem(QString());
        sizeComboBox->addItem(QString());
        sizeComboBox->addItem(QString());
        sizeComboBox->addItem(QString());
        sizeComboBox->addItem(QString());
        sizeComboBox->addItem(QString());
        sizeComboBox->addItem(QString());
        sizeComboBox->addItem(QString());
        sizeComboBox->addItem(QString());
        sizeComboBox->addItem(QString());
        sizeComboBox->setObjectName(QString::fromUtf8("sizeComboBox"));
        sizeComboBox->setGeometry(QRect(180, 350, 45, 30));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(sizeComboBox->sizePolicy().hasHeightForWidth());
        sizeComboBox->setSizePolicy(sizePolicy1);
        sizeComboBox->setMinimumSize(QSize(45, 30));
        sizeComboBox->setMaximumSize(QSize(45, 30));
        sizeComboBox->setFont(font);
        sizeComboBox->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"	background-color: rgb(255, 255, 255);\n"
"    border: 1px solid gray;\n"
"    border-radius: 3px;\n"
"    padding: 1px 2px 1px 2px;  /*\351\222\210\345\257\271\344\272\216\347\273\204\345\220\210\346\241\206\344\270\255\347\232\204\346\226\207\346\234\254\345\206\205\345\256\271*/\n"
"    /*min-width: 9em;   \347\273\204\345\220\210\346\241\206\347\232\204\346\234\200\345\260\217\345\256\275\345\272\246*/\n"
"}\n"
"QComboBox::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
"    width: 20px;\n"
"\n"
"    border-left-width: 1px;\n"
"    border-left-color: darkgray;\n"
"    border-left-style: solid; \n"
"    border-top-right-radius: 3px; \n"
"    border-bottom-right-radius: 3px;\n"
"}\n"
"QComboBox::down-arrow {\n"
"    image: url(:/images/QComboBox);\n"
"}\n"
"QComboBox::drop-down:hover { background-color: rgb(50, 50, 50,255);}"));
        layoutWidget = new QWidget(page);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(240, 350, 248, 32));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        boldToolButton = new QToolButton(layoutWidget);
        boldToolButton->setObjectName(QString::fromUtf8("boldToolButton"));
        boldToolButton->setMinimumSize(QSize(30, 30));
        boldToolButton->setMaximumSize(QSize(30, 30));
        boldToolButton->setStyleSheet(QString::fromUtf8("QToolButton { background-color: rgb(50, 50, 50,0); border-radius: 3px; color: rgb(255, 255, 255); }\n"
"QToolButton:hover { background-color: rgb(50, 50, 50,255);}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/bold.png"), QSize(), QIcon::Normal, QIcon::Off);
        boldToolButton->setIcon(icon);
        boldToolButton->setCheckable(true);

        horizontalLayout->addWidget(boldToolButton);

        italicToolButton = new QToolButton(layoutWidget);
        italicToolButton->setObjectName(QString::fromUtf8("italicToolButton"));
        italicToolButton->setMinimumSize(QSize(30, 30));
        italicToolButton->setMaximumSize(QSize(30, 30));
        italicToolButton->setStyleSheet(QString::fromUtf8("QToolButton { background-color: rgb(50, 50, 50,0); border-radius: 3px; color: rgb(255, 255, 255); }\n"
"QToolButton:hover { background-color: rgb(50, 50, 50,255);}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/italic.png"), QSize(), QIcon::Normal, QIcon::Off);
        italicToolButton->setIcon(icon1);
        italicToolButton->setCheckable(true);

        horizontalLayout->addWidget(italicToolButton);

        underlineToolButton = new QToolButton(layoutWidget);
        underlineToolButton->setObjectName(QString::fromUtf8("underlineToolButton"));
        underlineToolButton->setMinimumSize(QSize(30, 30));
        underlineToolButton->setMaximumSize(QSize(30, 30));
        underlineToolButton->setStyleSheet(QString::fromUtf8("QToolButton { background-color: rgb(50, 50, 50,0); border-radius: 3px; color: rgb(255, 255, 255); }\n"
"QToolButton:hover { background-color: rgb(50, 50, 50,255);}"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/under.png"), QSize(), QIcon::Normal, QIcon::Off);
        underlineToolButton->setIcon(icon2);
        underlineToolButton->setCheckable(true);

        horizontalLayout->addWidget(underlineToolButton);

        colorToolButton = new QToolButton(layoutWidget);
        colorToolButton->setObjectName(QString::fromUtf8("colorToolButton"));
        colorToolButton->setMinimumSize(QSize(30, 30));
        colorToolButton->setMaximumSize(QSize(30, 30));
        colorToolButton->setStyleSheet(QString::fromUtf8("QToolButton { background-color: rgb(50, 50, 50,0); border-radius: 3px; color: rgb(255, 255, 255); }\n"
"QToolButton:hover { background-color: rgb(50, 50, 50,255);}"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/color.png"), QSize(), QIcon::Normal, QIcon::Off);
        colorToolButton->setIcon(icon3);

        horizontalLayout->addWidget(colorToolButton);

        sendToolButton = new QToolButton(layoutWidget);
        sendToolButton->setObjectName(QString::fromUtf8("sendToolButton"));
        sendToolButton->setMinimumSize(QSize(30, 30));
        sendToolButton->setMaximumSize(QSize(30, 30));
        sendToolButton->setStyleSheet(QString::fromUtf8("QToolButton { background-color: rgb(50, 50, 50,0); border-radius: 3px; color: rgb(255, 255, 255); }\n"
"QToolButton:hover { background-color: rgb(50, 50, 50,255);}"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/send.png"), QSize(), QIcon::Normal, QIcon::Off);
        sendToolButton->setIcon(icon4);

        horizontalLayout->addWidget(sendToolButton);

        saveToolButton = new QToolButton(layoutWidget);
        saveToolButton->setObjectName(QString::fromUtf8("saveToolButton"));
        saveToolButton->setMinimumSize(QSize(30, 30));
        saveToolButton->setMaximumSize(QSize(30, 30));
        saveToolButton->setStyleSheet(QString::fromUtf8("QToolButton { background-color: rgb(50, 50, 50,0); border-radius: 3px; color: rgb(255, 255, 255); }\n"
"QToolButton:hover { background-color: rgb(50, 50, 50,255);}"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        saveToolButton->setIcon(icon5);

        horizontalLayout->addWidget(saveToolButton);

        clearToolButton = new QToolButton(layoutWidget);
        clearToolButton->setObjectName(QString::fromUtf8("clearToolButton"));
        clearToolButton->setMinimumSize(QSize(30, 30));
        clearToolButton->setMaximumSize(QSize(30, 30));
        clearToolButton->setStyleSheet(QString::fromUtf8("QToolButton { background-color: rgb(50, 50, 50,0); border-radius: 3px; color: rgb(255, 255, 255); }\n"
"QToolButton:hover { background-color: rgb(50, 50, 50,255);}"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/images/clear.png"), QSize(), QIcon::Normal, QIcon::Off);
        clearToolButton->setIcon(icon6);

        horizontalLayout->addWidget(clearToolButton);

        line_3 = new QFrame(page);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(10, 80, 480, 2));
        line_3->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 125);"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        toolButton_8 = new QToolButton(page);
        toolButton_8->setObjectName(QString::fromUtf8("toolButton_8"));
        toolButton_8->setGeometry(QRect(10, 8, 40, 40));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(40);
        sizePolicy2.setVerticalStretch(40);
        sizePolicy2.setHeightForWidth(toolButton_8->sizePolicy().hasHeightForWidth());
        toolButton_8->setSizePolicy(sizePolicy2);
        toolButton_8->setMinimumSize(QSize(40, 40));
        toolButton_8->setStyleSheet(QString::fromUtf8("QToolButton { background-color: rgb(50, 50, 50,0); border-radius: 3px; color: rgb(255, 255, 255); }"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/images/head.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_8->setIcon(icon7);
        toolButton_8->setIconSize(QSize(40, 40));
        label = new QLabel(page);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(80, 30, 161, 16));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font1.setPointSize(8);
        label->setFont(font1);
        label_2 = new QLabel(page);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(62, 5, 151, 25));
        label_2->setMinimumSize(QSize(100, 25));
        label_2->setBaseSize(QSize(100, 25));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font2.setPointSize(12);
        label_2->setFont(font2);
        layoutWidget1 = new QWidget(page);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 48, 248, 32));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        toolButton = new QToolButton(layoutWidget1);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        toolButton->setMinimumSize(QSize(30, 30));
        toolButton->setMaximumSize(QSize(30, 30));
        toolButton->setStyleSheet(QString::fromUtf8("QToolButton { background-color: rgb(50, 50, 50,0); border-radius: 3px; color: rgb(255, 255, 255); }\n"
"QToolButton:hover { background-color: rgb(50, 50, 50,255);}"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/images/mcallphone.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton->setIcon(icon8);
        toolButton->setIconSize(QSize(30, 30));

        horizontalLayout_2->addWidget(toolButton);

        toolButton_2 = new QToolButton(layoutWidget1);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));
        toolButton_2->setMinimumSize(QSize(30, 30));
        toolButton_2->setMaximumSize(QSize(30, 30));
        toolButton_2->setStyleSheet(QString::fromUtf8("QToolButton { background-color: rgb(50, 50, 50,0); border-radius: 3px; color: rgb(255, 255, 255); }\n"
"QToolButton:hover { background-color: rgb(50, 50, 50,255);}"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/images/video.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_2->setIcon(icon9);
        toolButton_2->setIconSize(QSize(30, 30));

        horizontalLayout_2->addWidget(toolButton_2);

        toolButton_3 = new QToolButton(layoutWidget1);
        toolButton_3->setObjectName(QString::fromUtf8("toolButton_3"));
        toolButton_3->setMinimumSize(QSize(30, 30));
        toolButton_3->setMaximumSize(QSize(30, 30));
        toolButton_3->setStyleSheet(QString::fromUtf8("QToolButton { background-color: rgb(50, 50, 50,0); border-radius: 3px; color: rgb(255, 255, 255); }\n"
"QToolButton:hover { background-color: rgb(50, 50, 50,255);}"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/images/control.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_3->setIcon(icon10);
        toolButton_3->setIconSize(QSize(30, 30));

        horizontalLayout_2->addWidget(toolButton_3);

        toolButton_4 = new QToolButton(layoutWidget1);
        toolButton_4->setObjectName(QString::fromUtf8("toolButton_4"));
        toolButton_4->setMinimumSize(QSize(30, 30));
        toolButton_4->setMaximumSize(QSize(30, 30));
        toolButton_4->setStyleSheet(QString::fromUtf8("QToolButton { background-color: rgb(50, 50, 50,0); border-radius: 3px; color: rgb(255, 255, 255); }\n"
"QToolButton:hover { background-color: rgb(50, 50, 50,255);}"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/images/file.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_4->setIcon(icon11);
        toolButton_4->setIconSize(QSize(30, 30));

        horizontalLayout_2->addWidget(toolButton_4);

        toolButton_5 = new QToolButton(layoutWidget1);
        toolButton_5->setObjectName(QString::fromUtf8("toolButton_5"));
        toolButton_5->setMinimumSize(QSize(30, 30));
        toolButton_5->setMaximumSize(QSize(30, 30));
        toolButton_5->setStyleSheet(QString::fromUtf8("QToolButton { background-color: rgb(50, 50, 50,0); border-radius: 3px; color: rgb(255, 255, 255); }\n"
"QToolButton:hover { background-color: rgb(50, 50, 50,255);}"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/images/table.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_5->setIcon(icon12);
        toolButton_5->setIconSize(QSize(30, 30));

        horizontalLayout_2->addWidget(toolButton_5);

        toolButton_6 = new QToolButton(layoutWidget1);
        toolButton_6->setObjectName(QString::fromUtf8("toolButton_6"));
        toolButton_6->setMinimumSize(QSize(30, 30));
        toolButton_6->setMaximumSize(QSize(30, 30));
        toolButton_6->setStyleSheet(QString::fromUtf8("QToolButton { background-color: rgb(50, 50, 50,0); border-radius: 3px; color: rgb(255, 255, 255); }\n"
"QToolButton:hover { background-color: rgb(50, 50, 50,255);}"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/images/people.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_6->setIcon(icon13);
        toolButton_6->setIconSize(QSize(30, 30));

        horizontalLayout_2->addWidget(toolButton_6);

        toolButton_7 = new QToolButton(layoutWidget1);
        toolButton_7->setObjectName(QString::fromUtf8("toolButton_7"));
        toolButton_7->setMinimumSize(QSize(30, 30));
        toolButton_7->setMaximumSize(QSize(30, 30));
        toolButton_7->setStyleSheet(QString::fromUtf8("QToolButton { background-color: rgb(50, 50, 50,0); border-radius: 3px; color: rgb(255, 255, 255); }\n"
"QToolButton:hover { background-color: rgb(50, 50, 50,255);}"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/images/software.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_7->setIcon(icon14);
        toolButton_7->setIconSize(QSize(30, 30));

        horizontalLayout_2->addWidget(toolButton_7);

        pushButton = new QPushButton(page);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(59, 30, 16, 16));
        pushButton->setMinimumSize(QSize(16, 16));
        pushButton->setMaximumSize(QSize(16, 16));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton { background-color: rgb(50, 50, 50,0); border-radius: 3px; color: rgb(255, 255, 255); }\n"
"QPushButton:hover { background-color: rgb(50, 50, 50,255);}"));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/images/star.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon15);
        userNumLabel = new QLabel(page);
        userNumLabel->setObjectName(QString::fromUtf8("userNumLabel"));
        userNumLabel->setGeometry(QRect(480, 460, 135, 30));
        userNumLabel->setMinimumSize(QSize(135, 30));
        userNumLabel->setMaximumSize(QSize(157, 41));
        QFont font3;
        font3.setPointSize(9);
        userNumLabel->setFont(font3);
        userNumLabel->setStyleSheet(QString::fromUtf8(""));
        userNumLabel->setAlignment(Qt::AlignCenter);
        layoutWidget2 = new QWidget(page);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(602, -1, 140, 32));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        menuButton = new MenuButton(layoutWidget2);
        menuButton->setObjectName(QString::fromUtf8("menuButton"));
        menuButton->setMinimumSize(QSize(30, 30));
        menuButton->setMaximumSize(QSize(30, 30));
        menuButton->setStyleSheet(QString::fromUtf8("QPushButton { background-color: rgb(50, 50, 50,0); border-radius: 3px; color: rgb(255, 255, 255); }\n"
"QPushButton:hover { background-color: rgb(50, 50, 50,255);}"));
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/images/menu.png"), QSize(), QIcon::Normal, QIcon::Off);
        menuButton->setIcon(icon16);

        horizontalLayout_3->addWidget(menuButton);

        minButton = new QToolButton(layoutWidget2);
        minButton->setObjectName(QString::fromUtf8("minButton"));
        minButton->setMinimumSize(QSize(30, 30));
        minButton->setMaximumSize(QSize(30, 30));
        minButton->setStyleSheet(QString::fromUtf8("QToolButton { background-color: rgb(50, 50, 50,0); border-radius: 3px; color: rgb(255, 255, 255); }\n"
"QToolButton:hover { background-color: rgb(50, 50, 50,255);}"));
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/images/min.png"), QSize(), QIcon::Normal, QIcon::Off);
        minButton->setIcon(icon17);

        horizontalLayout_3->addWidget(minButton);

        maxButton = new QToolButton(layoutWidget2);
        maxButton->setObjectName(QString::fromUtf8("maxButton"));
        maxButton->setMinimumSize(QSize(30, 30));
        maxButton->setMaximumSize(QSize(30, 30));
        maxButton->setStyleSheet(QString::fromUtf8("QToolButton { background-color: rgb(50, 50, 50,0); border-radius: 3px; color: rgb(255, 255, 255); }\n"
"QToolButton:hover { background-color: rgb(50, 50, 50,255);}"));
        QIcon icon18;
        icon18.addFile(QString::fromUtf8(":/images/max.png"), QSize(), QIcon::Normal, QIcon::Off);
        maxButton->setIcon(icon18);

        horizontalLayout_3->addWidget(maxButton);

        closeButton = new QToolButton(layoutWidget2);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        closeButton->setMinimumSize(QSize(30, 30));
        closeButton->setMaximumSize(QSize(30, 30));
        closeButton->setStyleSheet(QString::fromUtf8("QToolButton { background-color: rgb(50, 50, 50,0); border-radius: 3px; color: rgb(255, 255, 255); }\n"
"QToolButton:hover { background-color: rgb(50, 50, 50,255);}"));
        QIcon icon19;
        icon19.addFile(QString::fromUtf8(":/images/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        closeButton->setIcon(icon19);

        horizontalLayout_3->addWidget(closeButton);

        userTableWidget = new QTableWidget(page);
        if (userTableWidget->columnCount() < 3)
            userTableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem->setBackground(QColor(0, 0, 0));
        userTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignCenter);
        userTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setTextAlignment(Qt::AlignCenter);
        userTableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        userTableWidget->setObjectName(QString::fromUtf8("userTableWidget"));
        userTableWidget->setGeometry(QRect(480, 80, 255, 380));
        userTableWidget->setMinimumSize(QSize(255, 380));
        userTableWidget->setMaximumSize(QSize(255, 380));
        QFont font4;
        font4.setPointSize(8);
        userTableWidget->setFont(font4);
        userTableWidget->setStyleSheet(QString::fromUtf8("QTableWidget { background-color: rgb(255, 132, 139,0); border-radius: 3px; color: rgb(0,0,0); }"));
        userTableWidget->setAlternatingRowColors(false);
        userTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        userTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        userTableWidget->setShowGrid(false);
        userTableWidget->setGridStyle(Qt::SolidLine);
        userTableWidget->horizontalHeader()->setVisible(false);
        userTableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        userTableWidget->horizontalHeader()->setMinimumSectionSize(83);
        userTableWidget->horizontalHeader()->setDefaultSectionSize(83);
        userTableWidget->horizontalHeader()->setHighlightSections(false);
        userTableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        userTableWidget->horizontalHeader()->setStretchLastSection(false);
        userTableWidget->verticalHeader()->setVisible(false);
        userTableWidget->verticalHeader()->setMinimumSectionSize(30);
        userTableWidget->verticalHeader()->setHighlightSections(false);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        stackedWidget->addWidget(page_2);

        retranslateUi(Widget);

        sizeComboBox->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "QQ", nullptr));
        sendButton->setText(QCoreApplication::translate("Widget", "\345\217\221\351\200\201", nullptr));
        exitButton->setText(QCoreApplication::translate("Widget", "\345\205\263\351\227\255", nullptr));
        sizeComboBox->setItemText(0, QCoreApplication::translate("Widget", "9", nullptr));
        sizeComboBox->setItemText(1, QCoreApplication::translate("Widget", "10", nullptr));
        sizeComboBox->setItemText(2, QCoreApplication::translate("Widget", "11", nullptr));
        sizeComboBox->setItemText(3, QCoreApplication::translate("Widget", "12", nullptr));
        sizeComboBox->setItemText(4, QCoreApplication::translate("Widget", "13", nullptr));
        sizeComboBox->setItemText(5, QCoreApplication::translate("Widget", "14", nullptr));
        sizeComboBox->setItemText(6, QCoreApplication::translate("Widget", "15", nullptr));
        sizeComboBox->setItemText(7, QCoreApplication::translate("Widget", "16", nullptr));
        sizeComboBox->setItemText(8, QCoreApplication::translate("Widget", "17", nullptr));
        sizeComboBox->setItemText(9, QCoreApplication::translate("Widget", "18", nullptr));
        sizeComboBox->setItemText(10, QCoreApplication::translate("Widget", "19", nullptr));
        sizeComboBox->setItemText(11, QCoreApplication::translate("Widget", "20", nullptr));
        sizeComboBox->setItemText(12, QCoreApplication::translate("Widget", "21", nullptr));
        sizeComboBox->setItemText(13, QCoreApplication::translate("Widget", "22", nullptr));

#if QT_CONFIG(tooltip)
        boldToolButton->setToolTip(QCoreApplication::translate("Widget", "\345\212\240\347\262\227", nullptr));
#endif // QT_CONFIG(tooltip)
        boldToolButton->setText(QCoreApplication::translate("Widget", "...", nullptr));
#if QT_CONFIG(tooltip)
        italicToolButton->setToolTip(QCoreApplication::translate("Widget", "\345\200\276\346\226\234", nullptr));
#endif // QT_CONFIG(tooltip)
        italicToolButton->setText(QCoreApplication::translate("Widget", "...", nullptr));
#if QT_CONFIG(tooltip)
        underlineToolButton->setToolTip(QCoreApplication::translate("Widget", "\344\270\213\345\210\222\347\272\277", nullptr));
#endif // QT_CONFIG(tooltip)
        underlineToolButton->setText(QCoreApplication::translate("Widget", "...", nullptr));
#if QT_CONFIG(tooltip)
        colorToolButton->setToolTip(QCoreApplication::translate("Widget", "\346\233\264\346\224\271\345\255\227\344\275\223\351\242\234\350\211\262", nullptr));
#endif // QT_CONFIG(tooltip)
        colorToolButton->setText(QCoreApplication::translate("Widget", "...", nullptr));
#if QT_CONFIG(tooltip)
        sendToolButton->setToolTip(QCoreApplication::translate("Widget", "\344\274\240\350\276\223\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
        sendToolButton->setText(QCoreApplication::translate("Widget", "...", nullptr));
#if QT_CONFIG(tooltip)
        saveToolButton->setToolTip(QCoreApplication::translate("Widget", "\344\277\235\345\255\230\350\201\212\345\244\251\350\256\260\345\275\225", nullptr));
#endif // QT_CONFIG(tooltip)
        saveToolButton->setText(QCoreApplication::translate("Widget", "...", nullptr));
#if QT_CONFIG(tooltip)
        clearToolButton->setToolTip(QCoreApplication::translate("Widget", "\346\270\205\351\231\244\350\201\212\345\244\251\350\256\260\345\275\225", nullptr));
#endif // QT_CONFIG(tooltip)
        clearToolButton->setText(QCoreApplication::translate("Widget", "...", nullptr));
        toolButton_8->setText(QCoreApplication::translate("Widget", "...", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\346\260\270\350\277\234\347\232\204\347\245\236-\347\213\274\350\241\214", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "langx\346\260\270\350\277\234\347\232\204\347\245\236", nullptr));
#if QT_CONFIG(tooltip)
        toolButton->setToolTip(QCoreApplication::translate("Widget", "\345\217\221\350\265\267\350\257\255\351\237\263\351\200\232\350\257\235", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton->setText(QCoreApplication::translate("Widget", "...", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_2->setToolTip(QCoreApplication::translate("Widget", "\345\217\221\350\265\267\350\247\206\351\242\221\351\200\232\350\257\235", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_2->setText(QCoreApplication::translate("Widget", "...", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_3->setToolTip(QCoreApplication::translate("Widget", "\350\277\234\347\250\213\346\274\224\347\244\272", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_3->setText(QCoreApplication::translate("Widget", "...", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_4->setToolTip(QCoreApplication::translate("Widget", "\344\274\240\351\200\201\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_4->setText(QCoreApplication::translate("Widget", "...", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_5->setToolTip(QCoreApplication::translate("Widget", "\350\277\234\347\250\213\346\241\214\351\235\242", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_5->setText(QCoreApplication::translate("Widget", "...", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_6->setToolTip(QCoreApplication::translate("Widget", "\345\217\221\350\265\267\345\244\232\344\272\272\350\201\212\345\244\251", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_6->setText(QCoreApplication::translate("Widget", "...", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_7->setToolTip(QCoreApplication::translate("Widget", "\345\272\224\347\224\250", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_7->setText(QCoreApplication::translate("Widget", "...", nullptr));
        pushButton->setText(QString());
        userNumLabel->setText(QCoreApplication::translate("Widget", "\345\234\250\347\272\277\347\224\250\346\210\267\357\274\2320\344\272\272", nullptr));
#if QT_CONFIG(tooltip)
        menuButton->setToolTip(QCoreApplication::translate("Widget", "\347\232\256\350\202\244", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        menuButton->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(whatsthis)
        menuButton->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
#if QT_CONFIG(accessibility)
        menuButton->setAccessibleName(QString());
#endif // QT_CONFIG(accessibility)
#if QT_CONFIG(accessibility)
        menuButton->setAccessibleDescription(QString());
#endif // QT_CONFIG(accessibility)
        menuButton->setText(QString());
#if QT_CONFIG(tooltip)
        minButton->setToolTip(QCoreApplication::translate("Widget", "\346\234\200\345\260\217\345\214\226", nullptr));
#endif // QT_CONFIG(tooltip)
        minButton->setText(QCoreApplication::translate("Widget", "...", nullptr));
#if QT_CONFIG(tooltip)
        maxButton->setToolTip(QCoreApplication::translate("Widget", "\346\234\200\345\244\247\345\214\226", nullptr));
#endif // QT_CONFIG(tooltip)
        maxButton->setText(QCoreApplication::translate("Widget", "...", nullptr));
#if QT_CONFIG(tooltip)
        closeButton->setToolTip(QCoreApplication::translate("Widget", "\345\205\263\351\227\255", nullptr));
#endif // QT_CONFIG(tooltip)
        closeButton->setText(QCoreApplication::translate("Widget", "...", nullptr));
        QTableWidgetItem *___qtablewidgetitem = userTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("Widget", "\347\224\250\346\210\267\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = userTableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("Widget", "\344\270\273\346\234\272\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = userTableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("Widget", "IP\345\234\260\345\235\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
