
#include "widget.h"
#include "./ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->label->setStyleSheet("font-size:20pt;");
    mythread = new MyThread;
    connect(mythread, &MyThread::curNumber, ui->label, [&](int cnt){
//        ui->label->setText(QString::number(cnt));
        ui->label->setNum(cnt);
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    mythread->start();
}
