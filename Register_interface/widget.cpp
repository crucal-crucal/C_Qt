#include "widget.h"
#include "ui_widget.h"

#include <QMovie>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QPixmap pixmap;
    pixmap.load(":/image/1/1.gif");

    //QSize PixSize=pixmap.size();

    QMovie *movie = new QMovie(":/image/1/1.gif");
    ui->Lab_photo->setMovie(movie);
    movie->start();
    ui->Lab_photo->setScaledContents(1);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_Pbt_regist_clicked()
{
    /*this->hide();
    Dlg = new MyDialog(this);
    Dlg->resize(800, 600);
    Dlg->exec();*/

    D = new MyDialog(this);
    D->show();
    D->exec();
}

