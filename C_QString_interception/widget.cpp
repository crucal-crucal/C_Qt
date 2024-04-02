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


void Widget::on_Btn_front_clicked()
{
    //截取字符串
    QString str1=ui->Cbox_str1->currentText();
    ui->plainTextEdit->appendPlainText(str1);
    ui->plainTextEdit->appendPlainText(str1[0]);
    ui->plainTextEdit->appendPlainText(str1[str1.size()-1]);
}


void Widget::on_Btn_left_clicked()
{
    //截取字符串
    QString str1=ui->Cbox_str1->currentText();
    QString s="left(2): ";
    s+=str1.mid(0, 2);
    ui->plainTextEdit->appendPlainText(s);
    s.clear();
    s="right(2): ";
    s+=str1.mid(str1.size()-2);
    ui->plainTextEdit->appendPlainText(s);
}

void Widget::on_Btn_first_clicked()
{
    //截取字符串
    ui->plainTextEdit->appendPlainText(tr("\n===first(), last()函数测试"));
    QString str1=ui->Cbox_str1->currentText(), str2=ui->Cbox_str2->currentText();
    ui->plainTextEdit->appendPlainText(QString("%6=%1\n%7=%2\n%3\n%4\n").arg(str1).arg(str2)
                                       .arg(str1.first(11)).arg(str1.last(9))
                                       .arg("str1").arg("str2"));
}


void Widget::on_Btn_section_clicked()
{
    //截取字符串
    QString str1=ui->Cbox_str1->currentText();
    ui->plainTextEdit->appendPlainText(str1.section('\\', 0, 0));
}


void Widget::on_Btn_empty_clicked()
{
    //判断是否为空
    ui->plainTextEdit->appendPlainText(tr("\n===isNull()函数测试"));
    QString str1=ui->Cbox_str1->currentText(), str2=ui->Cbox_str2->currentText();
    //qDebug()<<str1.isNull();
    str1.clear();
    str2="";
    ui->plainTextEdit->appendPlainText(QString("%1=%2\n%3=%4\n\n%5=%6\n%7=%8\n")
                                       .arg("str1.isNull()").arg(str1.isNull()?"True":"false")
                                       .arg("str1.isEmpty").arg(str1.isEmpty()?"True":"false")
                                       .arg("str2.isNull()").arg(str2.isNull()?"True":"false")
                                       .arg("str2.isEmpty").arg(str2.isEmpty()?"True":"false"));
    str2.clear();
    ui->plainTextEdit->appendPlainText(QString("%5\n\n%1=%2\n%3=%4")
                                       .arg("str2.isNull()").arg(str2.isNull()?"True":"false")
                                       .arg("str2.isEmpty").arg(str2.isEmpty()?"True":"false")
                                       .arg("str2.clear()后"));
}


void Widget::on_Btn_resize_clicked()
{
    //重定义大小，也可从定义字符
    ui->plainTextEdit->appendPlainText(tr("\n===resize()函数测试"));
    QString str1=ui->Cbox_str1->currentText();
    str1.clear();
    str1.resize(5, '0');
    ui->plainTextEdit->appendPlainText(str1);
    QString str2("00000哈哈哈哈哈");
    str2.resize(10);
    ui->plainTextEdit->appendPlainText(str2);
}


void Widget::on_Btn_size_clicked()
{
    //返回大小，count，长度
    ui->plainTextEdit->appendPlainText(tr("\n===size(),count(),length()函数测试"));
    QString str1=ui->Cbox_str1->currentText();
    ui->plainTextEdit->appendPlainText(QString("%1\n%2=%3\n%4=%5\n%6=%7").arg(str1)
                                       .arg(tr("size()")).arg(str1.size())
                                       .arg("count()").arg(str1.count())
                                       .arg("length()").arg(str1.length()));
}


void Widget::on_Btn_fill_clicked()
{
    //赋值
    ui->plainTextEdit->appendPlainText(tr("\n===fill()函数测试"));
    QString str1;
    str1.fill('X', 5);
    ui->plainTextEdit->appendPlainText(str1);
    str1.fill('A', 2);
    ui->plainTextEdit->appendPlainText(str1);
    ui->plainTextEdit->appendPlainText(QString("%1\n").arg("哈哈哈"));
}


void Widget::on_Btn_index_clicked()
{
    //查找字符串索引，字符索引
    ui->plainTextEdit->appendPlainText(tr("\n===indexOf(),lastIndexOf()函数测试"));
    QString str1=ui->Cbox_str1->currentText(), str2=ui->Cbox_str2->currentText();
    ui->plainTextEdit->appendPlainText(QString("%1 = %2\n%3 = %4\n%5= %6\n%7= %8\n").arg("str1").arg(str1)
                                       .arg("str2").arg(str2).arg("indexOf()")
                                       .arg(str1.indexOf('\\')).arg("lastIndexOf")
                                       .arg(str1.lastIndexOf('\\')));
}


void Widget::on_Btn_contains_clicked()
{
    //查找字符串是否存在
    ui->plainTextEdit->appendPlainText(tr("\n===contains()函数测试"));
    QString str1=ui->Cbox_str1->currentText(), str2=ui->Cbox_str2->currentText();
    ui->plainTextEdit->appendPlainText(QString("%1\n%2\n%3= %4\n").arg(str1).arg(str2)
                                       .arg("contains()= =")
                                       .arg(str1.contains("G")?"True":"False"));
}


void Widget::on_Btn_endswith_clicked()
{
    //查看字符串是否在开头或者结尾
    ui->plainTextEdit->appendPlainText(tr("\n===endsWith(),startsWith()函数测试"));
    QString str1=ui->Cbox_str1->currentText(), str2=ui->Cbox_str2->currentText();
    ui->plainTextEdit->appendPlainText(QString("%1 = %2\n%3 = %4\n%5= %6\n%7= %8\n")
                                       .arg("str1").arg(str1)
                                       .arg("str2").arg(str2).arg("endsWith")
                                       .arg(str1.endsWith("aples")?"True":"False")
                                       .arg("startsWith")
                                       .arg(str1.startsWith("GG")?"True":"False"));
}


void Widget::on_Btn_count_clicked()
{
    //返回字符或字符串出现的次数
    ui->plainTextEdit->appendPlainText(tr("\n===count()统计子字符串出现的次数"));
    QString str1=ui->Cbox_str1->currentText(), str2=ui->Cbox_str2->currentText();
    ui->plainTextEdit->appendPlainText(QString("%1 = %2\n%3 = %4\n%5= %6").arg("str1").arg(str1)
                                       .arg("str2").arg(str2).arg("count()")
                                       .arg(str1.count(str2)));
}


void Widget::on_Btn_trimmed_clicked()
{
    //删除前后空白的字符串trimmed
    //除去开头结尾的空格，中间多个空格留一个，多余字符删除
    ui->plainTextEdit->appendPlainText(tr("\n===trimmed(),simplified()函数测试"));
    QString str1=ui->Cbox_str1->currentText();
    ui->plainTextEdit->appendPlainText(QString("%1 = %2\n%3 = %4\n%5= %6\n")
                                       .arg("str1").arg(str1)
                                       .arg("trimmed()").arg(str1.trimmed())
                                       .arg("simplified()").arg(str1.simplified()));
}


void Widget::on_Btn_insert_clicked()
{
    //插入
    ui->plainTextEdit->appendPlainText(tr("\n===insert()函数测试"));
    QString str1("It ");
    str1.insert(3, "is great");
    //qDebug()<<str1.size();
    ui->plainTextEdit->appendPlainText(QString("%1\n%2\n").arg(str1).arg(str1.insert(5, "n't")));
}


void Widget::on_Btn_remove_clicked()
{
    //删除特定字符串，删除范围内的字符串
    ui->plainTextEdit->appendPlainText(tr("\n===remove()移除特定的字符"));
    QString str1="你们，我们，他们";
    ui->plainTextEdit->appendPlainText(QString("%1= %2\n%1= %3\n")
                                       .arg("str1").arg(str1)
                                       .arg(str1.remove("们")));
    ui->plainTextEdit->appendPlainText(tr("\n===remove()移除右侧N个字符"));
    str1.clear();str1="G:\\Qt6Book\\QtSamples\\qw.cpp";
    //qDebug()<<str1;
    ui->plainTextEdit->appendPlainText(QString("%1\n%2").arg(str1).
                                       arg((str1.remove(str1.size()-6, str1.size()))));
}


void Widget::on_Btn_repalce_clicked()
{
    //替换字符串
    ui->plainTextEdit->appendPlainText(tr("\n===replace(),替换字符串"));
    QString str1("It is great"), str2("wonderful"), str3("OK!");
    ui->plainTextEdit->appendPlainText(QString("%1\n%2\n%3\n").arg(str1)
                                       .arg(str1.replace(6, str2.size(), "wonderful"))
                                       .arg((str1.replace(6, str2.size(), "OK!"))));
}

