#include "mydialog.h"
#include "ui_mydialog.h"

MyDialog::MyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    ui->setupUi(this);
}

MyDialog::~MyDialog()
{
    delete ui;
}

void MyDialog::on_Xiahuaxian_clicked(bool checked)
{
    QFont font=ui->plainTextEdit->font();
    font.setUnderline(checked);//下划线
    ui->plainTextEdit->setFont(font);
}


void MyDialog::on_Xieti_clicked(bool checked)
{
    QFont font=ui->plainTextEdit->font();
    font.setItalic(checked);//斜体
    ui->plainTextEdit->setFont(font);
}


void MyDialog::on_Cuti_clicked(bool checked)
{
    QFont font=ui->plainTextEdit->font();
    font.setBold(checked);//粗体
    ui->plainTextEdit->setFont(font);
}


void MyDialog::on_Black_clicked()
{
    QPalette plet =ui->plainTextEdit->palette();
    plet.setColor(QPalette::Text, Qt::black);
    ui->plainTextEdit->setPalette(plet);
}


void MyDialog::on_Red_clicked()
{
    QPalette plet =ui->plainTextEdit->palette();
    plet.setColor(QPalette::Text, Qt::red);
    ui->plainTextEdit->setPalette(plet);
}


void MyDialog::on_Blue_clicked()
{
    QPalette plet =ui->plainTextEdit->palette();
    plet.setColor(QPalette::Text, Qt::blue);
    ui->plainTextEdit->setPalette(plet);
}

void MyDialog::on_exit_clicked()
{
    this->hide();
    Dlg = new MyDialog (this);
    Dlg->parentWidget();
}

