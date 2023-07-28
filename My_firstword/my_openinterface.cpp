#include "my_openinterface.h"
#include "ui_my_openinterface.h"

My_openInterface::My_openInterface(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::My_openInterface)
{
    ui->setupUi(this);
    this->setWindowTitle("新建文本");

    // 新建界面
    connect(ui->Btn_yes, &QPushButton::clicked, this, &My_openInterface::newinterFace);
    // 原始界面
    connect(ui->Btn_no, &QPushButton::clicked, this, &My_openInterface::oldinterFace);
}

My_openInterface::~My_openInterface()
{
    delete ui;
}

void My_openInterface::newinterFace()
{
    this->hide();
    emit Yes();
}

void My_openInterface::oldinterFace()
{
    this->hide();
    emit No();
}

