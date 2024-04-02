#include "widget.h"
#include "ui_widget.h"

#include <QtEndian>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    int a = 60;
    QByteArray array(reinterpret_cast<const char*>(&a), sizeof(a));
    qDebug() << qFromLittleEndian<int>(array.constData());
    qDebug() << qFromBigEndian<int>(array.constData());
}

Widget::~Widget()
{
    delete ui;
}

