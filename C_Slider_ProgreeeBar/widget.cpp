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


void Widget::on_Dial_valueChanged(int value)
{
    ui->progressBar->setValue(value);
    ui->horizontalSlider->setValue(value);
    ui->horizontalScrollBar->setValue(value);
    ui->lcdNumber->display(value);
}


void Widget::on_horizontalSlider_valueChanged(int value)
{
    ui->Dial->setValue(value);
}


void Widget::on_horizontalScrollBar_valueChanged(int value)
{
    ui->Dial->setValue(value);
}


void Widget::on_R_Btn_Bin_clicked()
{
    ui->lcdNumber->setBinMode();
}


void Widget::on_radioButton_5_clicked()
{
    int num=ui->lcdNumber->value();
    ui->lcdNumber->display(QString::number(num, 16));
}


void Widget::on_checkBox_Visible_clicked(bool checked)
{
    ui->progressBar->setTextVisible(checked);
}


void Widget::on_checkBox_inverted_clicked(bool checked)
{
    ui->progressBar->setInvertedAppearance(checked);
}


void Widget::on_R_Btn_percentage_clicked()
{
    QString s="%p%";
    ui->progressBar->setFormat(s);
}


void Widget::on_R_Btn_point_clicked()
{

    QString s="%v";
    ui->progressBar->setFormat(s);
}


void Widget::on_R_Btn_OCT_clicked()
{
    ui->lcdNumber->setOctMode();
}


void Widget::on_R_Btn_HEX_clicked()
{
    ui->lcdNumber->setHexMode();
}

