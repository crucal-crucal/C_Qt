#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    boy = new person("lds", 10, this);
    boy->setProperty("sex", "boy"), boy->setProperty("occupation", "student"), boy->setProperty("father", "cf");
    connect(boy, &person::ageChanged, this, &Widget::on_ageChanged);

    girl = new person("LDS", 10, this);
    girl->setProperty("sex", "girl"), girl->setProperty("occupation", "teacher"), girl->setProperty("father", "cf");
    connect(girl, &person::ageChanged, this, &Widget::on_ageChanged);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_Btn_Meta_clicked()
{
    //qDebug()<<this->metaObject()->classInfo(0).name();
    QString s="Name: ";
    s+=this->metaObject()->classInfo(0).name();
    s+=", Value: ", s+=this->metaObject()->classInfo(0).value();
    ui->plainTextEdit->appendPlainText(s), s.clear();

    s="Company_Name: ";
    s+=this->metaObject()->classInfo(1).name();
    s+=", Value: ", s+=this->metaObject()->classInfo(1).value();
    ui->plainTextEdit->appendPlainText(s), s.clear();
}


void Widget::on_spinBox_boy_valueChanged(int arg1)
{
    boy->setAge(arg1);
}

void Widget::on_ageChanged()
{
    person *people = qobject_cast<person *> (sender());
    QString name = "Name: ", age = "Age: ", sex = "Sex: ", occupation = "Occupation: ", father = "father: ";
    name += people->property("name").toString(), age += people->property("age").toString(),
    sex += people->property("sex").toString(), occupation += people->property("occupation").toString(),
    father += people->property("father").toString();

    //将name,age,sex,occupation等连接在一起
    QString info = QString("%1, %2, %3, %4, %5").arg(name).arg(age).arg(sex).arg(occupation).arg(father);
    ui->plainTextEdit->appendPlainText(info);
}

void Widget::on_Btn_boy_clicked()
{
    int age = boy->readAge();
    ui->spinBox_boy->setValue(++age);
}


void Widget::on_spinBox_girl_valueChanged(int arg1)
{
    girl->setAge(arg1);
}


void Widget::on_Btn_girl_clicked()
{
    int age = girl->readAge();
    ui->spinBox_girl->setValue(++age);
}

