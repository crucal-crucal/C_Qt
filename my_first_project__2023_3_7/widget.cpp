#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

void Widget::emitsignal()
{
    emit mysignal();
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->Btn_close->move(875-75, 0);
    ui->Btn_close->setText("CLOSE");
    //connect(ui->Btn_close, &QPushButton::clicked, this, &Widget::close);//系统槽
    //发送的类和接收的类在同一个线程里，默认为0
//    connect(ui->Btn_close, &QPushButton::clicked, this,[&](){
//        this->close();
//    });//lambda表达式， 自己写的槽
    connect(ui->Btn_close, SIGNAL(clicked()), this, SLOT(mySlot()));//qt4
    connect(this, &Widget::mysignal, this, [&](){
        QString s("老师：下课了！");//c++ string
        qDebug()<<s;//输出
    });
    connect(this, &Widget::mysignal, this, [&]()
    {
        QString s("学生：吃饭了！");
        qDebug()<<s;
    });
    emitsignal();
//    QPushButton *btn_Full = new QPushButton;
//    btn_Full->setParent(this);
//    btn_Full->setText("Full");
    QPushButton *btn_Full = new QPushButton("Full", this);

//    btn_Full->setFixedSize(75, 24);
    btn_Full->resize(75, 24);

    btn_Full->move(875-(75<<1), 0);
    connect(btn_Full, &QPushButton::clicked, this, &Widget::showFullScreen);

    QPushButton *btn_Normal = new QPushButton;
//    btn_Normal->setFixedSize(75, 24);
    btn_Normal->resize(75, 24);
    btn_Normal->setParent(this);
    btn_Normal->setText("Normal");
    btn_Normal->move(875-(75<<2), 0);
    connect(btn_Normal, &QPushButton::clicked, this, &Widget::showNormal);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mySlot()
{
    this->close();
}

void Widget::student()
{
    QString s("学生：吃饭了！");
    qDebug()<<s;
}

void Widget::teacher()
{
    QString s("老师：下课了");
    qDebug()<<s;
}

