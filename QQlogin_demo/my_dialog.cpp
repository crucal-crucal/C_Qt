#include "my_dialog.h"
#include "ui_my_dialog.h"

My_Dialog::My_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::My_Dialog)
{
    ui->setupUi(this);
}

My_Dialog::~My_Dialog()
{
    delete ui;
}

void My_Dialog::on_Btn_close_clicked()
{
    this->close();
}

void My_Dialog::on_Btn_min_clicked()
{
    this->showMinimized();
}

