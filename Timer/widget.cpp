#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->groupBox_time->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);//定时器分组框垂直方向固定尺寸
    ui->groupBox_precise->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);//精度垂直方向固定尺寸

    tm = new QTimer(this);
    tm->stop();//开始先停止计时器
    tm->setTimerType(Qt::CoarseTimer);//定时器精度等级
    ui->rad_Coarse->setChecked(true);//设置默认值
    connect(tm,SIGNAL(timeout()),this,SLOT(do_timer_timeout()));   //关联定时器的信号与槽
}

Widget::~Widget()
{
    delete ui;
}


void Widget::do_timer_timeout()
{
    QDateTime currenttime = QDateTime::currentDateTime();//获取当前时间

    ui->lcdNumber_h->display(currenttime.time().hour());
    ui->lcdNumber_m->display(currenttime.time().minute());
    ui->lcdNumber_s->display(currenttime.time().second());
    if(tm->isSingleShot())//单次定时
    {
        int t = currenttime.time().msec();//获取当前毫秒数
        //int t = m_counter.msec();
        QString str = QString("流逝的时间：%1毫秒").arg(t);
        ui->lab_ElapsedTime->setText(str);

        ui->Btn_start->setEnabled(true);//开始按钮可用
        ui->Btn_stop->setEnabled(false);//停止按钮不可用
        ui->Btn_dynamic->setEnabled(true);
    }
}

void Widget::do_timer_shot()
{
    QApplication::beep();
    QDateTime currenttime = QDateTime::currentDateTime();//获取当前时间

    int t = currenttime.time().msec();//获取当前毫秒数
    //int t = m_counter.msec();
    QString str=QString("流逝的时间：%1毫秒").arg(t);
    ui->lab_ElapsedTime->setText(str);
    ui->Btn_dynamic->setEnabled(true);
}

void Widget::on_Btn_start_clicked()
{
    tm->setInterval(ui->spinBox->value());

    //单次定时或连续定时
    if(ui->rad_Coarse->isChecked()) tm->setSingleShot(false);//连续定时
    else tm->setSingleShot(true);

    //定时器精度
    if (ui->RBtn_precise->isChecked())
        tm->setTimerType(Qt::PreciseTimer);
    else if (ui->RBtn_coarse->isChecked())
        tm->setTimerType(Qt::CoarseTimer);
    else
        tm->setTimerType(Qt::VeryCoarseTimer);


    tm->start();     //启动定时器
    //m_counter.start();    //启动计时器
    ui->Btn_start->setEnabled(false);
    ui->Btn_dynamic->setEnabled(false);
    ui->Btn_stop->setEnabled(true);
}


void Widget::on_Btn_stop_clicked()
{
    tm->stop();    //定时器停止
    QDateTime currenttime = QDateTime::currentDateTime();//获取当前时间
    int t = currenttime.time().msec();//获取当前毫秒数
    //qDebug()<<t;
    //int t = m_counter.msec();
    int ms= t % 1000;  //余数毫秒
    int sec=t/1000;    //整秒

    QString str=QString("流逝的时间：%1秒，%2毫秒").arg(sec).arg(ms,3,10,QChar('0'));
    ui->lab_ElapsedTime->setText(str); //显示流逝的时间

    ui->Btn_start->setEnabled(true);
    ui->Btn_dynamic->setEnabled(true);
    ui->Btn_stop->setEnabled(false);
}



void Widget::on_Btn_dynamic_clicked()
{
    int intv=ui->spinBox->value();  //定时周期
    QTimer::singleShot(intv,Qt::PreciseTimer,this,&Widget::do_timer_shot);
    //m_counter.start();   //启动计时器
    ui->Btn_dynamic->setEnabled(false);
}

