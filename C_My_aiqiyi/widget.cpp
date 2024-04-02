
#include "widget.h"
#include "./ui_widget.h"

void Widget::init()
{
    recommmend_check = true;
//    Mywidget *w = new Mywidget(this);
    w.resize(N);
    for (int i=0;i<N;i++)
    {
        w[i] = new Mywidget(this);
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(100, 130));
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item, w[i]);
    }


//    QString s[] = {"推荐", "电视剧", "电影", "动漫", "少儿"};

    btn1 = new QPushButton("推荐", ui->listWidget_bar);
    item = new QListWidgetItem(ui->listWidget_bar);
    btn1->setFixedSize(50, 20);
    item->setSizeHint(btn1->size());
    ui->listWidget_bar->setItemWidget(item, btn1);
    connect(btn1, &QPushButton::clicked, this, Widget::recommend);

    btn2 = new QPushButton("电视剧", ui->listWidget_bar);
    item = new QListWidgetItem(ui->listWidget_bar);
    btn2->setFixedSize(50, 20);
    item->setSizeHint(btn2->size());
    ui->listWidget_bar->setItemWidget(item, btn2);
    connect(btn2, &QPushButton::clicked, this, Widget::TV);

    btn3 = new QPushButton("电影", ui->listWidget_bar);
    item = new QListWidgetItem(ui->listWidget_bar);
    btn3->setFixedSize(50, 20);
    item->setSizeHint(btn3->size());
    ui->listWidget_bar->setItemWidget(item, btn3);
    connect(btn3, &QPushButton::clicked, this, Widget::movie);

    btn4 = new QPushButton("动漫", ui->listWidget_bar);
    item = new QListWidgetItem(ui->listWidget_bar);
    btn4->setFixedSize(50, 20);
    item->setSizeHint(btn4->size());
    ui->listWidget_bar->setItemWidget(item, btn4);
    connect(btn4, &QPushButton::clicked, this, Widget::annimation);

    btn5 = new QPushButton("少儿", ui->listWidget_bar);
    item = new QListWidgetItem(ui->listWidget_bar);
    btn5->setFixedSize(50, 20);
    item->setSizeHint(btn5->size());
    ui->listWidget_bar->setItemWidget(item, btn5);
    connect(btn5, &QPushButton::clicked, this, Widget::Children);
}

void Widget::recommend()
{
    if(!recommmend_check)
    {
        recommmend_check = true, TV_check = false, movie_check = false, annimation_check = false, children_check = false;
        ui->listWidget->clear();
        for (int i=0;i<5;i++)
        {
            Mywidget *w = new Mywidget(this);
            QListWidgetItem *item = new QListWidgetItem();
            item->setSizeHint(QSize(100, 130));
            ui->listWidget->addItem(item);
            ui->listWidget->setItemWidget(item, w);
        }
    }
}

void Widget::TV()
{
    if(!TV_check)
    {
        recommmend_check = false, TV_check = true, movie_check = false, annimation_check = false, children_check = false;
        ui->listWidget->clear();
    }
}

void Widget::movie()
{
    if(!movie_check)
    {
        recommmend_check = false, TV_check = false, movie_check = true, annimation_check = false, children_check = false;
        ui->listWidget->clear();
    }
}

void Widget::annimation()
{
    if(!annimation_check)
    {
        recommmend_check = false, TV_check = false, movie_check = false, annimation_check = true, children_check = false;
        ui->listWidget->clear();
    }
}

void Widget::Children()
{
    if(!children_check)
    {
        recommmend_check = false, TV_check = false, movie_check = false, annimation_check = false, children_check = true;
        ui->listWidget->clear();
    }
}


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    init();

    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl("https://www.baidu.com")));
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    if(reply->error() == QNetworkReply::NoError)
    {
        qDebug()<<QString(reply->readAll())<<"ok";
    }
    else
    {
        qDebug()<<"Error:"<<reply->errorString();
    }
    reply->deleteLater();
}

Widget::~Widget()
{
    delete ui;
}

