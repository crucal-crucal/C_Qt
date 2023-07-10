#include "widget.h"
#include "ui_widget.h"

#include <QIcon>
#include <QMap>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->comboBox, QComboBox::currentTextChanged, this, [&](const QString str){
        ui->plainTextEdit->insertPlainText(str+"\n");
    });
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_Btn_initList_clicked()
{
    QIcon icon;
    icon.addFile(":/image/apple.png");

    ui->comboBox->clear();
    for (int i=0;i<20;i++)
    {
        ui->comboBox->addItem(icon, QString("Item %1").arg(i));
    }

    //QStringList strlist;
    //strlist<<"北京"<<"上海"<<"天津"<<"河北"<<"山东"<<"陕西";
    //for (auto &c:strlist)
    //ui->comboBox->addItem(c);

    /*connect(ui->comboBox, QComboBox::currentTextChanged, this, [&](const QString str){
       ui->plainTextEdit->insertPlainText(str+"\n");
    });*/
}


void Widget::on_checkBox_clicked(bool checked)
{
    ui->comboBox->setEditable(checked);
}


void Widget::on_Btn_initCity_clicked()
{
    QMap<QString, int> mp;
    mp.insert("北京",10);
    mp.insert("上海",21);
    mp.insert("天津",22);
    mp.insert("大连",411);
    mp.insert("锦州",416);
    mp.insert("徐州",516);
    mp.insert("福州",591);
    mp.insert("青岛",532);

    ui->comboBox_2->clear();
    for (auto &c : mp.keys())
    {
        ui->comboBox_2->addItem(c, mp.value(c));
    }
    connect(ui->comboBox_2,&QComboBox::currentTextChanged,this,[&](const QString &text){
        ui->plainTextEdit->insertPlainText(text+"\n");
    });
}

