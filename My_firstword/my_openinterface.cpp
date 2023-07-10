#include "my_openinterface.h"
#include "ui_my_openinterface.h"

My_openInterface::My_openInterface(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::My_openInterface)
{
    ui->setupUi(this);
}

My_openInterface::~My_openInterface()
{
    delete ui;
}

