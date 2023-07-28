#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //定时器
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
}

Widget::~Widget()
{
    delete ui;
}

//控制方向
void Widget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Up:
        if(Move_flag!=Sn_Down)
        {
            Move_flag=Sn_Up;
        }
        break;
    case Qt::Key_Down:
        if(Move_flag!=Sn_Up)
        {
            Move_flag=Sn_Down;
        }
        break;
    case Qt::Key_Left:
        if(Move_flag!=Sn_Right)
        {
            Move_flag=Sn_Left;
        }break;
    case Qt::Key_Right:
        if(Move_flag!=Sn_Left)
        {
            Move_flag=Sn_Right;
        }
        break;
    case Qt::Key_Space:
        if(GameStart==0)
        {
            GameStart=1;
            timer->start(my_time);
        }
        else
        {
            GameStart=0;
            timer->stop();
        }
        break;
    default:
        break;
    }
}

void Widget::timeout()
{
    switch(Move_flag)
    {
    case Sn_Up:
        break;
    case Sn_Down:
        break;
    case Sn_Right:
        break;
    case Sn_Left:
        break;
    default:
        break;
    }
}

void Widget::addTop()
{
    QPointF leftTop;
    QPointF rightBotom;
    if(snake[0].y()-nodeHeight < 0)
    {
        leftTop = QPointF(snake[0].x(), this->height()-nodeHeight);
        rightBotom = QPointF(snake[0].x()+nodeWidth, this->height());
    }
    else
    {
        leftTop = QPointF(snake[0].x(), snake[0].y()-nodeHeight);
        rightBotom = snake[0].topRight();
    }
    snake.insert(0, QRectF(leftTop, rightBotom));
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPixmap pix;
    pix.load(":/image/background.png");
}

