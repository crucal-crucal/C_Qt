#include "form.h"
#include "ui_form.h"

Form::Form(QString fileName,qint64 fileSize,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    setFixedHeight(60);
    ui->label_name->setText(fileName);
    m_fileSize = fileSize;
    ui->progressBar->setFixedHeight(10);
    ui->progressBar->setMinimum(0);
    if(m_fileSize>1024)
        ui->progressBar->setMaximum(fileSize/1024);
    else
        ui->progressBar->setMaximum(fileSize);
}

Form::~Form()
{
    delete ui;
}

void Form::updateProcess(qint64 recSize)
{
    if(m_fileSize>1024)
        ui->progressBar->setValue(recSize/1024);
    else
        ui->progressBar->setValue(recSize);
    ui->label_process->setText(QString("%1/%2").arg(recSize).arg(m_fileSize));
    update();
}

void Form::setStatus(bool bl)
{
    ui->label->setFixedSize(20,20);
    if(bl){
        ui->label->setStyleSheet("background-color:rgb(50,205,50);border-radius:5px;");
    }else{
        ui->label->setStyleSheet("background-color:red;border-radius:5px;");
    }
}
