#include "my_findpasswd.h"
#include "ui_my_findpasswd.h"
#include <lgoin.h>

My_findpasswd::My_findpasswd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::My_findpasswd)
{
    ui->setupUi(this);
}

My_findpasswd::~My_findpasswd()
{
    delete ui;
}

void My_findpasswd::on_Btn_cancel_clicked()
{
    this->close();
}


void My_findpasswd::on_Btn_min_clicked()
{
    this->close();
}


void My_findpasswd::on_Btn_close_clicked()
{
    this->close();
}

