#include "widget.h"
#include "ui_widget.h"

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


void Widget::on_Underline_clicked(bool checked)
{
    QFont font = ui->plainTextEdit->font();//获取plainTextEdit的文本
    font.setUnderline(checked);//是否添加下划线
    ui->plainTextEdit->setFont(font);//应用到plainTextEdit文本上
}

void Widget::on_Italic_clicked(bool checked)
{
    QFont font = ui->plainTextEdit->font();
    font.setItalic(checked);//斜体
    ui->plainTextEdit->setFont(font);
}

void Widget::on_Red_clicked(bool checked)
{
    QPalette plet = ui->plainTextEdit->palette();
    if(checked)
    {
        plet.setColor(QPalette::Text,Qt::red);
    }
    else
    {
        plet.setColor(QPalette::Text,Qt::black);
    }
    ui->plainTextEdit->setPalette(plet);
}





void Widget::on_Bold_clicked(bool checked)
{
    QFont font=ui->plainTextEdit->font();
    font.setBold(checked);//加粗
    ui->plainTextEdit->setFont(font);
}


void Widget::on_Black_clicked()
{
    QPalette plet=ui->plainTextEdit->palette();
    plet.setColor(QPalette::Text,Qt::black);
    ui->plainTextEdit->setPalette(plet);
}


void Widget::on_Blue_clicked()
{
    QPalette plet=ui->plainTextEdit->palette();
    plet.setColor(QPalette::Text,Qt::blue);
    ui->plainTextEdit->setPalette(plet);
}

