
#include "widget.h"
#include "./ui_widget.h"
#include "QSqlDatabase"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    qDebug()<<QSqlDatabase::drivers();
}

Widget::~Widget()
{
    delete ui;
}


