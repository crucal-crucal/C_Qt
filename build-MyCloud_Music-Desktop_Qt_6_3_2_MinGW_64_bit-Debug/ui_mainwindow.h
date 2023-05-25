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
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
//#include "circularbannerwidget.h"
//#include "exclusivecustomwidget.h"
//#include "newestmusicwidget.h"
//#include "ranklistwidget.h"
//#include "singerwidget.h"
//#include "songlistwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *titleWidget;
    QLabel *logoLabel;
    QPushButton *leftButton;
    QPushButton *rightButton;
    QPushButton *microphoneButton;
    QPushButton *iconButton;
    QPushButton *personButton;
    QPushButton *vipButton;
    QPushButton *skinButton;
    QPushButton *settingsButton;
    QPushButton *messageButton;
    QPushButton *miniButton;
    QPushButton *minimizedButton;
    QPushButton *maximizedButton;
    QPushButton *closeButton;
    QLabel *messageCountLabel;
    QLabel *separatorLabel;
    QLineEdit *searchEdit;
    QPushButton *searchButton;
    QWidget *bottomWidget;
    QPushButton *lastMusicButton;
    QPushButton *playAndStopButton;
    QPushButton *nextMusicButton;
    QPushButton *loopStateButton;
    QPushButton *lyricButton;
    QPushButton *qualityButton;
    QPushButton *soundEffectButton;
    QPushButton *volumeButton;
    QPushButton *karaokeButton;
    QPushButton *playlistButton;
    QPushButton *musicIconButton;
    QLabel *playedTimeLabel;
    QLabel *durationTimeLabel;
    QSlider *musicProgressSlider;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *musicNameLabel;
    QSpacerItem *horizontalSpacer_2;
    QLabel *singerLabel;
    QPushButton *likeButton;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QListWidget *listT1;
    QLabel *myMusicLabel;
    QListWidget *listT2;
    QLabel *createSonglistLabel;
    QPushButton *addButton;
    QListWidget *listT3;
    QTabWidget *homeTabWidget;
    QWidget *personalityRecommendWidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_6;
    //CircularBannerWidget *bannerWidget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *songlistBtn1;
    QPushButton *songlistBtn2;
    QSpacerItem *horizontalSpacer;
    QWidget *recommedSongListWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *recommendSongBtn1;
    QLabel *song1infoLabel;
    QVBoxLayout *verticalLayout_2;
    QPushButton *recommendSongBtn2;
    QLabel *song2infoLabel;
    QVBoxLayout *verticalLayout_3;
    QPushButton *recommendSongBtn3;
    QLabel *song3infoLabel;
    QVBoxLayout *verticalLayout_4;
    QPushButton *recommendSongBtn4;
    QLabel *song4infoLabel;
    QVBoxLayout *verticalLayout_5;
    QPushButton *recommendSongBtn5;
    QLabel *song5infoLabel;
    //ExclusiveCustomWidget *exclusiveCustomWidget;
//    SongListWidget *songListWIdget;
//    RankListWidget *rankListWidget;
//    SingerWidget *singerWidget;
//    NewestMusicWidget *newestMusicWidget;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1019, 682);
        MainWindow->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border:0px;\n"
"}"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        titleWidget = new QWidget(centralWidget);
        titleWidget->setObjectName(QString::fromUtf8("titleWidget"));
        titleWidget->setGeometry(QRect(0, 0, 1022, 60));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(titleWidget->sizePolicy().hasHeightForWidth());
        titleWidget->setSizePolicy(sizePolicy);
        logoLabel = new QLabel(titleWidget);
        logoLabel->setObjectName(QString::fromUtf8("logoLabel"));
        logoLabel->setGeometry(QRect(10, 10, 145, 40));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(logoLabel->sizePolicy().hasHeightForWidth());
        logoLabel->setSizePolicy(sizePolicy1);
        leftButton = new QPushButton(titleWidget);
        leftButton->setObjectName(QString::fromUtf8("leftButton"));
        leftButton->setGeometry(QRect(230, 20, 24, 24));
        sizePolicy1.setHeightForWidth(leftButton->sizePolicy().hasHeightForWidth());
        leftButton->setSizePolicy(sizePolicy1);
        rightButton = new QPushButton(titleWidget);
        rightButton->setObjectName(QString::fromUtf8("rightButton"));
        rightButton->setGeometry(QRect(260, 20, 24, 24));
        sizePolicy1.setHeightForWidth(rightButton->sizePolicy().hasHeightForWidth());
        rightButton->setSizePolicy(sizePolicy1);
        microphoneButton = new QPushButton(titleWidget);
        microphoneButton->setObjectName(QString::fromUtf8("microphoneButton"));
        microphoneButton->setGeometry(QRect(470, 20, 24, 24));
        sizePolicy1.setHeightForWidth(microphoneButton->sizePolicy().hasHeightForWidth());
        microphoneButton->setSizePolicy(sizePolicy1);
        iconButton = new QPushButton(titleWidget);
        iconButton->setObjectName(QString::fromUtf8("iconButton"));
        iconButton->setGeometry(QRect(560, 15, 30, 30));
        sizePolicy1.setHeightForWidth(iconButton->sizePolicy().hasHeightForWidth());
        iconButton->setSizePolicy(sizePolicy1);
        personButton = new QPushButton(titleWidget);
        personButton->setObjectName(QString::fromUtf8("personButton"));
        personButton->setGeometry(QRect(590, 20, 91, 21));
        sizePolicy1.setHeightForWidth(personButton->sizePolicy().hasHeightForWidth());
        personButton->setSizePolicy(sizePolicy1);
        vipButton = new QPushButton(titleWidget);
        vipButton->setObjectName(QString::fromUtf8("vipButton"));
        vipButton->setGeometry(QRect(690, 17, 60, 25));
        skinButton = new QPushButton(titleWidget);
        skinButton->setObjectName(QString::fromUtf8("skinButton"));
        skinButton->setGeometry(QRect(750, 20, 16, 16));
        settingsButton = new QPushButton(titleWidget);
        settingsButton->setObjectName(QString::fromUtf8("settingsButton"));
        settingsButton->setGeometry(QRect(790, 20, 16, 16));
        messageButton = new QPushButton(titleWidget);
        messageButton->setObjectName(QString::fromUtf8("messageButton"));
        messageButton->setGeometry(QRect(830, 20, 16, 16));
        miniButton = new QPushButton(titleWidget);
        miniButton->setObjectName(QString::fromUtf8("miniButton"));
        miniButton->setGeometry(QRect(880, 20, 16, 16));
        minimizedButton = new QPushButton(titleWidget);
        minimizedButton->setObjectName(QString::fromUtf8("minimizedButton"));
        minimizedButton->setGeometry(QRect(915, 20, 16, 16));
        maximizedButton = new QPushButton(titleWidget);
        maximizedButton->setObjectName(QString::fromUtf8("maximizedButton"));
        maximizedButton->setGeometry(QRect(950, 20, 16, 16));
        closeButton = new QPushButton(titleWidget);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        closeButton->setGeometry(QRect(980, 20, 16, 16));
        messageCountLabel = new QLabel(titleWidget);
        messageCountLabel->setObjectName(QString::fromUtf8("messageCountLabel"));
        messageCountLabel->setGeometry(QRect(843, 14, 21, 16));
        separatorLabel = new QLabel(titleWidget);
        separatorLabel->setObjectName(QString::fromUtf8("separatorLabel"));
        separatorLabel->setGeometry(QRect(857, 20, 16, 17));
        searchEdit = new QLineEdit(titleWidget);
        searchEdit->setObjectName(QString::fromUtf8("searchEdit"));
        searchEdit->setGeometry(QRect(287, 16, 171, 31));
        searchButton = new QPushButton(titleWidget);
        searchButton->setObjectName(QString::fromUtf8("searchButton"));
        searchButton->setGeometry(QRect(293, 26, 15, 15));
        bottomWidget = new QWidget(centralWidget);
        bottomWidget->setObjectName(QString::fromUtf8("bottomWidget"));
        bottomWidget->setGeometry(QRect(0, 600, 1021, 72));
        lastMusicButton = new QPushButton(bottomWidget);
        lastMusicButton->setObjectName(QString::fromUtf8("lastMusicButton"));
        lastMusicButton->setGeometry(QRect(450, 23, 15, 15));
        playAndStopButton = new QPushButton(bottomWidget);
        playAndStopButton->setObjectName(QString::fromUtf8("playAndStopButton"));
        playAndStopButton->setGeometry(QRect(500, 15, 31, 31));
        playAndStopButton->setCheckable(true);
        nextMusicButton = new QPushButton(bottomWidget);
        nextMusicButton->setObjectName(QString::fromUtf8("nextMusicButton"));
        nextMusicButton->setGeometry(QRect(570, 23, 15, 15));
        loopStateButton = new QPushButton(bottomWidget);
        loopStateButton->setObjectName(QString::fromUtf8("loopStateButton"));
        loopStateButton->setGeometry(QRect(390, 15, 31, 28));
        lyricButton = new QPushButton(bottomWidget);
        lyricButton->setObjectName(QString::fromUtf8("lyricButton"));
        lyricButton->setGeometry(QRect(630, 18, 25, 25));
        qualityButton = new QPushButton(bottomWidget);
        qualityButton->setObjectName(QString::fromUtf8("qualityButton"));
        qualityButton->setGeometry(QRect(790, 20, 31, 31));
        soundEffectButton = new QPushButton(bottomWidget);
        soundEffectButton->setObjectName(QString::fromUtf8("soundEffectButton"));
        soundEffectButton->setGeometry(QRect(840, 20, 31, 31));
        volumeButton = new QPushButton(bottomWidget);
        volumeButton->setObjectName(QString::fromUtf8("volumeButton"));
        volumeButton->setGeometry(QRect(890, 20, 31, 28));
        karaokeButton = new QPushButton(bottomWidget);
        karaokeButton->setObjectName(QString::fromUtf8("karaokeButton"));
        karaokeButton->setGeometry(QRect(940, 20, 31, 31));
        playlistButton = new QPushButton(bottomWidget);
        playlistButton->setObjectName(QString::fromUtf8("playlistButton"));
        playlistButton->setGeometry(QRect(980, 20, 31, 31));
        musicIconButton = new QPushButton(bottomWidget);
        musicIconButton->setObjectName(QString::fromUtf8("musicIconButton"));
        musicIconButton->setGeometry(QRect(0, 0, 70, 70));
        playedTimeLabel = new QLabel(bottomWidget);
        playedTimeLabel->setObjectName(QString::fromUtf8("playedTimeLabel"));
        playedTimeLabel->setGeometry(QRect(290, 50, 40, 16));
        durationTimeLabel = new QLabel(bottomWidget);
        durationTimeLabel->setObjectName(QString::fromUtf8("durationTimeLabel"));
        durationTimeLabel->setGeometry(QRect(690, 50, 40, 16));
        musicProgressSlider = new QSlider(bottomWidget);
        musicProgressSlider->setObjectName(QString::fromUtf8("musicProgressSlider"));
        musicProgressSlider->setGeometry(QRect(335, 50, 350, 17));
        musicProgressSlider->setOrientation(Qt::Horizontal);
        widget = new QWidget(bottomWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(94, 10, 122, 48));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        musicNameLabel = new QLabel(widget);
        musicNameLabel->setObjectName(QString::fromUtf8("musicNameLabel"));

        gridLayout->addWidget(musicNameLabel, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 1, 1, 1);

        singerLabel = new QLabel(widget);
        singerLabel->setObjectName(QString::fromUtf8("singerLabel"));

        gridLayout->addWidget(singerLabel, 1, 0, 1, 1);

        likeButton = new QPushButton(widget);
        likeButton->setObjectName(QString::fromUtf8("likeButton"));

        gridLayout->addWidget(likeButton, 1, 1, 1, 1);

        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(0, 60, 201, 541));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 199, 539));
        listT1 = new QListWidget(scrollAreaWidgetContents);
        listT1->setObjectName(QString::fromUtf8("listT1"));
        listT1->setGeometry(QRect(0, 0, 200, 250));
        myMusicLabel = new QLabel(scrollAreaWidgetContents);
        myMusicLabel->setObjectName(QString::fromUtf8("myMusicLabel"));
        myMusicLabel->setGeometry(QRect(0, 250, 201, 16));
        listT2 = new QListWidget(scrollAreaWidgetContents);
        listT2->setObjectName(QString::fromUtf8("listT2"));
        listT2->setGeometry(QRect(0, 270, 200, 200));
        listT2->setIconSize(QSize(0, 0));
        createSonglistLabel = new QLabel(scrollAreaWidgetContents);
        createSonglistLabel->setObjectName(QString::fromUtf8("createSonglistLabel"));
        createSonglistLabel->setGeometry(QRect(0, 470, 121, 21));
        addButton = new QPushButton(scrollAreaWidgetContents);
        addButton->setObjectName(QString::fromUtf8("addButton"));
        addButton->setGeometry(QRect(170, 470, 21, 21));
        listT3 = new QListWidget(scrollAreaWidgetContents);
        listT3->setObjectName(QString::fromUtf8("listT3"));
        listT3->setGeometry(QRect(0, 490, 201, 50));
        scrollArea->setWidget(scrollAreaWidgetContents);
        homeTabWidget = new QTabWidget(centralWidget);
        homeTabWidget->setObjectName(QString::fromUtf8("homeTabWidget"));
        homeTabWidget->setGeometry(QRect(220, 70, 780, 531));
        personalityRecommendWidget = new QWidget();
        personalityRecommendWidget->setObjectName(QString::fromUtf8("personalityRecommendWidget"));
        layoutWidget = new QWidget(personalityRecommendWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 790, 496));
        verticalLayout_6 = new QVBoxLayout(layoutWidget);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
//        bannerWidget = new CircularBannerWidget(layoutWidget);
//        bannerWidget->setObjectName(QString::fromUtf8("bannerWidget"));
//        bannerWidget->setMinimumSize(QSize(788, 240));

        //verticalLayout_6->addWidget(bannerWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        songlistBtn1 = new QPushButton(layoutWidget);
        songlistBtn1->setObjectName(QString::fromUtf8("songlistBtn1"));
        songlistBtn1->setMinimumSize(QSize(84, 28));
        songlistBtn1->setMaximumSize(QSize(84, 28));
        QFont font;
        font.setPointSize(15);
        songlistBtn1->setFont(font);
        songlistBtn1->setFlat(false);

        horizontalLayout_2->addWidget(songlistBtn1);

        songlistBtn2 = new QPushButton(layoutWidget);
        songlistBtn2->setObjectName(QString::fromUtf8("songlistBtn2"));
        songlistBtn2->setMinimumSize(QSize(21, 21));
        songlistBtn2->setMaximumSize(QSize(21, 21));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/homeTab/recommend/\345\217\263\347\256\255\345\244\264.png"), QSize(), QIcon::Normal, QIcon::Off);
        songlistBtn2->setIcon(icon);

        horizontalLayout_2->addWidget(songlistBtn2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_6->addLayout(horizontalLayout_2);

        recommedSongListWidget = new QWidget(layoutWidget);
        recommedSongListWidget->setObjectName(QString::fromUtf8("recommedSongListWidget"));
        recommedSongListWidget->setMinimumSize(QSize(788, 212));
        horizontalLayout = new QHBoxLayout(recommedSongListWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        recommendSongBtn1 = new QPushButton(recommedSongListWidget);
        recommendSongBtn1->setObjectName(QString::fromUtf8("recommendSongBtn1"));
        recommendSongBtn1->setMinimumSize(QSize(125, 125));
        recommendSongBtn1->setMaximumSize(QSize(125, 125));

        verticalLayout->addWidget(recommendSongBtn1);

        song1infoLabel = new QLabel(recommedSongListWidget);
        song1infoLabel->setObjectName(QString::fromUtf8("song1infoLabel"));
        song1infoLabel->setMinimumSize(QSize(125, 0));
        song1infoLabel->setMaximumSize(QSize(120, 16777215));
        song1infoLabel->setWordWrap(true);

        verticalLayout->addWidget(song1infoLabel);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        recommendSongBtn2 = new QPushButton(recommedSongListWidget);
        recommendSongBtn2->setObjectName(QString::fromUtf8("recommendSongBtn2"));
        recommendSongBtn2->setMinimumSize(QSize(125, 125));
        recommendSongBtn2->setMaximumSize(QSize(125, 125));

        verticalLayout_2->addWidget(recommendSongBtn2);

        song2infoLabel = new QLabel(recommedSongListWidget);
        song2infoLabel->setObjectName(QString::fromUtf8("song2infoLabel"));
        song2infoLabel->setMinimumSize(QSize(125, 0));
        song2infoLabel->setMaximumSize(QSize(120, 16777215));
        song2infoLabel->setWordWrap(true);

        verticalLayout_2->addWidget(song2infoLabel);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        recommendSongBtn3 = new QPushButton(recommedSongListWidget);
        recommendSongBtn3->setObjectName(QString::fromUtf8("recommendSongBtn3"));
        recommendSongBtn3->setMinimumSize(QSize(125, 125));
        recommendSongBtn3->setMaximumSize(QSize(125, 125));

        verticalLayout_3->addWidget(recommendSongBtn3);

        song3infoLabel = new QLabel(recommedSongListWidget);
        song3infoLabel->setObjectName(QString::fromUtf8("song3infoLabel"));
        song3infoLabel->setMinimumSize(QSize(125, 0));
        song3infoLabel->setMaximumSize(QSize(120, 16777215));
        song3infoLabel->setWordWrap(true);

        verticalLayout_3->addWidget(song3infoLabel);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        recommendSongBtn4 = new QPushButton(recommedSongListWidget);
        recommendSongBtn4->setObjectName(QString::fromUtf8("recommendSongBtn4"));
        recommendSongBtn4->setMinimumSize(QSize(125, 125));
        recommendSongBtn4->setMaximumSize(QSize(125, 125));

        verticalLayout_4->addWidget(recommendSongBtn4);

        song4infoLabel = new QLabel(recommedSongListWidget);
        song4infoLabel->setObjectName(QString::fromUtf8("song4infoLabel"));
        song4infoLabel->setMinimumSize(QSize(125, 0));
        song4infoLabel->setMaximumSize(QSize(120, 16777215));
        song4infoLabel->setWordWrap(true);

        verticalLayout_4->addWidget(song4infoLabel);


        horizontalLayout->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        recommendSongBtn5 = new QPushButton(recommedSongListWidget);
        recommendSongBtn5->setObjectName(QString::fromUtf8("recommendSongBtn5"));
        recommendSongBtn5->setMinimumSize(QSize(125, 125));
        recommendSongBtn5->setMaximumSize(QSize(125, 125));

        verticalLayout_5->addWidget(recommendSongBtn5);

        song5infoLabel = new QLabel(recommedSongListWidget);
        song5infoLabel->setObjectName(QString::fromUtf8("song5infoLabel"));
        song5infoLabel->setMinimumSize(QSize(125, 0));
        song5infoLabel->setMaximumSize(QSize(120, 16777215));
        song5infoLabel->setWordWrap(true);

        verticalLayout_5->addWidget(song5infoLabel);


        horizontalLayout->addLayout(verticalLayout_5);


        verticalLayout_6->addWidget(recommedSongListWidget);

        homeTabWidget->addTab(personalityRecommendWidget, QString());
//        exclusiveCustomWidget = new ExclusiveCustomWidget();
//        exclusiveCustomWidget->setObjectName(QString::fromUtf8("exclusiveCustomWidget"));
//        homeTabWidget->addTab(exclusiveCustomWidget, QString());
//        songListWIdget = new SongListWidget();
//        songListWIdget->setObjectName(QString::fromUtf8("songListWIdget"));
//        homeTabWidget->addTab(songListWIdget, QString());
//        rankListWidget = new RankListWidget();
//        rankListWidget->setObjectName(QString::fromUtf8("rankListWidget"));
//        homeTabWidget->addTab(rankListWidget, QString());
//        singerWidget = new SingerWidget();
//        singerWidget->setObjectName(QString::fromUtf8("singerWidget"));
//        homeTabWidget->addTab(singerWidget, QString());
//        newestMusicWidget = new NewestMusicWidget();
//        newestMusicWidget->setObjectName(QString::fromUtf8("newestMusicWidget"));
//        homeTabWidget->addTab(newestMusicWidget, QString());
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        homeTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        logoLabel->setText(QString());
        leftButton->setText(QString());
        rightButton->setText(QString());
        microphoneButton->setText(QString());
        iconButton->setText(QString());
        personButton->setText(QCoreApplication::translate("MainWindow", "username", nullptr));
        vipButton->setText(QString());
        skinButton->setText(QString());
        settingsButton->setText(QString());
        messageButton->setText(QString());
        miniButton->setText(QString());
        minimizedButton->setText(QString());
        maximizedButton->setText(QString());
        closeButton->setText(QString());
        messageCountLabel->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        separatorLabel->setText(QCoreApplication::translate("MainWindow", "|", nullptr));
        searchButton->setText(QString());
        lastMusicButton->setText(QString());
        playAndStopButton->setText(QString());
        nextMusicButton->setText(QString());
        loopStateButton->setText(QString());
        lyricButton->setText(QString());
        qualityButton->setText(QString());
        soundEffectButton->setText(QString());
        volumeButton->setText(QString());
        karaokeButton->setText(QString());
        playlistButton->setText(QString());
        musicIconButton->setText(QString());
        playedTimeLabel->setText(QCoreApplication::translate("MainWindow", "00:00", nullptr));
        durationTimeLabel->setText(QCoreApplication::translate("MainWindow", "00:00", nullptr));
        musicNameLabel->setText(QCoreApplication::translate("MainWindow", "musicname", nullptr));
        singerLabel->setText(QCoreApplication::translate("MainWindow", "singer", nullptr));
        likeButton->setText(QString());
        myMusicLabel->setText(QCoreApplication::translate("MainWindow", "\346\210\221\347\232\204\351\237\263\344\271\220", nullptr));
        createSonglistLabel->setText(QCoreApplication::translate("MainWindow", "\345\210\233\345\273\272\347\232\204\346\255\214\345\215\225", nullptr));
        addButton->setText(QString());
        songlistBtn1->setText(QCoreApplication::translate("MainWindow", "\346\216\250\350\215\220\346\255\214\345\215\225", nullptr));
        songlistBtn2->setText(QString());
        recommendSongBtn1->setText(QString());
        song1infoLabel->setText(QString());
        recommendSongBtn2->setText(QString());
        song2infoLabel->setText(QString());
        recommendSongBtn3->setText(QString());
        song3infoLabel->setText(QString());
        recommendSongBtn4->setText(QString());
        song4infoLabel->setText(QString());
        recommendSongBtn5->setText(QString());
        song5infoLabel->setText(QString());
        homeTabWidget->setTabText(homeTabWidget->indexOf(personalityRecommendWidget), QCoreApplication::translate("MainWindow", "\344\270\252\346\200\247\346\216\250\350\215\220", nullptr));
//        homeTabWidget->setTabText(homeTabWidget->indexOf(exclusiveCustomWidget), QCoreApplication::translate("MainWindow", "\344\270\223\345\261\236\345\256\232\345\210\266", nullptr));
//        homeTabWidget->setTabText(homeTabWidget->indexOf(songListWIdget), QCoreApplication::translate("MainWindow", "\346\255\214\345\215\225", nullptr));
//        homeTabWidget->setTabText(homeTabWidget->indexOf(rankListWidget), QCoreApplication::translate("MainWindow", "\346\216\222\350\241\214\346\246\234", nullptr));
//        homeTabWidget->setTabText(homeTabWidget->indexOf(singerWidget), QCoreApplication::translate("MainWindow", "\346\255\214\346\211\213", nullptr));
//        homeTabWidget->setTabText(homeTabWidget->indexOf(newestMusicWidget), QCoreApplication::translate("MainWindow", "\346\234\200\346\226\260\351\237\263\344\271\220", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
