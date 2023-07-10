#include "my_register.h"
#include "ui_my_register.h"

My_register::My_register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::My_register)
{
    ui->setupUi(this);
}

My_register::~My_register()
{
    delete ui;
}

void My_register::on_Btn_close_clicked()
{
    this->close();
}

void My_register::on_Btn_min_clicked()
{
    this->showMinimized();
}

