<<<<<<< HEAD
#include "widget.h"
#include "ui_widget.h"

#include <QDir>
#include <QFileDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    butterfly.resize(butterflynum);
    for (auto &c : butterfly)
    {
        c = new MyLabel(this);
        auto x = rand() % width();
        auto y = rand() % height();
        c->move(x, y);//初始位置
    }

    player = new QMediaPlayer;
    this->output = new QAudioOutput(this);
    player->setAudioOutput(output);
    output->setVolume(0.2);//设置音量
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_Btn_music_clicked()
{
    //QString curPath = QDir::currentPath();//当前路径
    QString filname = QFileDialog::getOpenFileName(this, "open a file",
                                                    "D:\\CloudMusic\\WAVmusic",
                                                    "音频文件(*.mp3 *.wav *wma);;所有文件(*.*)");
    //qDebug()<<filname;
    player->setSource(QUrl::fromLocalFile(filname));
    player->play();
}

=======
#include "widget.h"
#include "ui_widget.h"

#include <QDir>
#include <QFileDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    butterfly.resize(butterflynum);
    for (auto &c : butterfly)
    {
        c = new MyLabel(this);
        auto x = rand() % width();
        auto y = rand() % height();
        c->move(x, y);//初始位置
    }

    player = new QMediaPlayer;
    this->output = new QAudioOutput(this);
    player->setAudioOutput(output);
    output->setVolume(0.2);//设置音量
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_Btn_music_clicked()
{
    //QString curPath = QDir::currentPath();//当前路径
    QString filname = QFileDialog::getOpenFileName(this, "open a file",
                                                    "D:\\CloudMusic\\WAVmusic",
                                                    "音频文件(*.mp3 *.wav *wma);;所有文件(*.*)");
    //qDebug()<<filname;
    player->setSource(QUrl::fromLocalFile(filname));
    player->play();
}

>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
