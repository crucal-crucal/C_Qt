#include "widget.h"
#include "ui_widget.h"
#include <iostream>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_Btn_sum_clicked()
{
    int num=ui->Edit_num->text().toInt();
    double price=ui->Edit_price->text().toDouble();
    double sum=num*price;
    ui->Edit_sum->setText(QString::number(sum, 'sum', 3));
    ui->Edit_sum->setText(QString::number(ui->Spx_num->value()*ui->Spx_double->value(), ' ', 2));
}


void Widget::on_Btn_debug_clicked()
{
    qDebug()<<ui->Edit_num->text();
    qDebug()<<ui->Edit_price->text();
    qDebug()<<ui->Edit_sum->text();
}


void Widget::on_Btn_DEC_clicked()
{
    QString s=ui->Edit_DEC->text();//读入字符串，字符串转化为int默认为十进制，所以不用转化
    ui->Edit_DEC->setText(s.setNum(s.toInt(), 10));
    ui->Edit_BIN->setText(QString::number(s.toInt(), 2));
    ui->Edit_HEX->setText(QString::number(s.toInt(), 16).toUpper());
}


void Widget::on_Btn_BIN_clicked()
{
    QString s=ui->Edit_BIN->text();//读入字符串
    bool ok;
    int val=s.toInt(&ok, 2);//转化为2进制
    ui->Edit_DEC->setText(QString::number(val, 10));
    ui->Edit_BIN->setText(QString::number(val, 2));
    ui->Edit_HEX->setText(QString::number(val, 16).toUpper());
}


void Widget::on_Btn_HEX_clicked()
{
    QString s=ui->Edit_HEX->text();//同理
    bool ok;
    int val=s.toInt(&ok, 16);
    ui->Edit_DEC->setText(QString::number(val, 10));
    ui->Edit_BIN->setText(QString::number(val, 2));
    ui->Edit_HEX->setText(QString::number(val, 16).toUpper());
}

