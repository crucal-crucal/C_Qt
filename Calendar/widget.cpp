#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_Btn_Time_clicked()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();//读取当前日期时间
    ui->timeEdit->setTime(currentDateTime.time());//设置时间
    ui->lineEdit_time->setText(currentDateTime.time().toString("hh:mm:ss"));//将时间转化为字符串

    ui->dateEdit->setDate(currentDateTime.date());
    ui->lineEdit_date->setText(currentDateTime.date().toString("yyyy-MM-dd"));

    ui->dateTimeEdit->setDateTime(currentDateTime);
    ui->lineEdit_time_date->setText(currentDateTime.toString("yyyy/MM/dd H:mm:ss"));
}


void Widget::on_Btn_settime_clicked()
{
    QString str = ui->lineEdit_time->text();
    str=str.trimmed();//去掉开头结尾可能多余的空格
    if(!str.isEmpty())
    {
        QTime tm = QTime::fromString(str, "hh:mm:ss");//QString转化为QTime
        ui->timeEdit->setTime(tm);
    }
}


void Widget::on_Btn_setdate_clicked()
{
    QString str = ui->lineEdit_date->text();
    str=str.trimmed();
    if(!str.isEmpty())
    {
        QDate date = QDate::fromString(str, "yyyy-MM-dd");
        ui->dateEdit->setDate(date);
    }
}


void Widget::on_Btn_settd_clicked()
{
    QString str = ui->lineEdit_time_date->text();
    str=str.trimmed();
    if(!str.isEmpty())
    {
        QDateTime datetime = QDateTime::fromString(str, "yyyy/MM/dd HH:mm:ss");
        ui->dateTimeEdit->setDateTime(datetime);
    }
}


void Widget::on_calendarWidget_clicked(const QDate &date)
{
    //qDebug()<<ui->calendarWidget->selectedDate();
    //qDebug()<<date;
    ui->lineEdit_cdate->setText(date.toString("yyyy-MM-dd"));//获取日历日期
}

