#include "mylabel.h"

MyLabel::MyLabel(QWidget *parent)
    : QLabel{parent}
{
    tm = new QTimer(this);
    connect(tm,SIGNAL(timeout()),this,SLOT(fly()));   //关联定时器的信号与槽
    tm->start(200);
}

void MyLabel::fly()
{
    int op1 = rand()%10, op2 = rand()%15;
    if(f)
    {
        pixmap = QString(":/images/down.png");
        f=0;
    }
    else
    {
        pixmap = QString(":/images/up.png");
        f=1;
    }
    this->setPixmap(pixmap);
    this->resize(pixmap.size()/3);
    this->setScaledContents(true);//填充

    auto posx=this->x(), posy=this->y();//记录当前位置
    if(this->x()>this->parentWidget()->width()) posx=0;//超出边界初始化
    if(this->y()>this->parentWidget()->height()) posy=0;

    this->move(posx+op1, posy+op2);
}
