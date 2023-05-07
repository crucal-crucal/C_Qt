#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_Xiahuaxian_clicked(bool checked)
{
    QFont font=ui->plainTextEdit->font();
    font.setUnderline(checked);//下划线
    ui->plainTextEdit->setFont(font);
}


void Dialog::on_Xieti_clicked(bool checked)
{
    QFont font=ui->plainTextEdit->font();
    font.setItalic(checked);//斜体
    ui->plainTextEdit->setFont(font);
}


void Dialog::on_Cuti_clicked(bool checked)
{
    QFont font=ui->plainTextEdit->font();
    font.setBold(checked);//粗体
    ui->plainTextEdit->setFont(font);
}


void Dialog::on_Black_clicked()
{
    QPalette plet =ui->plainTextEdit->palette();
    plet.setColor(QPalette::Text, Qt::black);
    ui->plainTextEdit->setPalette(plet);
}


void Dialog::on_Red_clicked()
{
    QPalette plet =ui->plainTextEdit->palette();
    plet.setColor(QPalette::Text, Qt::red);
    ui->plainTextEdit->setPalette(plet);
}


void Dialog::on_Blue_clicked()
{
    QPalette plet =ui->plainTextEdit->palette();
    plet.setColor(QPalette::Text, Qt::blue);
    ui->plainTextEdit->setPalette(plet);
}
