<<<<<<< HEAD
#include "form.h"
#include "ui_form.h"

Form::Form(QString fileName, qint64 fileSize, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    setFixedHeight(60);
    ui->label_name->setText(fileName);
    m_fileSize = fileSize;
    ui->progressBar->setFixedHeight(10);
    ui->progressBar->setMinimum(0);
    auto size = m_fileSize>1024 ? fileSize/1024 : fileSize;
    ui->progressBar->setMaximum(size);
}

Form::~Form()
{
    delete ui;
}


void Form::updateProcess(qint64 recSize)
{
    auto size = m_fileSize>1024 ? recSize/1024 : recSize;
    ui->progressBar->setMaximum(size);

    ui->label_process->setText(QString("%1 / %2").arg(recSize).arg(m_fileSize));
    update();
}

void Form::setStatus(bool bl)
{
    ui->label->setFixedSize(20, 20);

    QString sheet = bl ? "background-color:rgb(50,205,50);border-radius:5px;" :
                        "background-color:red;border-radius:5px;";
    ui->label->setStyleSheet(sheet);
}
=======
#include "form.h"
#include "ui_form.h"

Form::Form(QString fileName, qint64 fileSize, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    setFixedHeight(60);
    ui->label_name->setText(fileName);
    m_fileSize = fileSize;
    ui->progressBar->setFixedHeight(10);
    ui->progressBar->setMinimum(0);
    auto size = m_fileSize>1024 ? fileSize/1024 : fileSize;
    ui->progressBar->setMaximum(size);
}

Form::~Form()
{
    delete ui;
}


void Form::updateProcess(qint64 recSize)
{
    auto size = m_fileSize>1024 ? recSize/1024 : recSize;
    ui->progressBar->setMaximum(size);

    ui->label_process->setText(QString("%1 / %2").arg(recSize).arg(m_fileSize));
    update();
}

void Form::setStatus(bool bl)
{
    ui->label->setFixedSize(20, 20);

    QString sheet = bl ? "background-color:rgb(50,205,50);border-radius:5px;" :
                        "background-color:red;border-radius:5px;";
    ui->label->setStyleSheet(sheet);
}
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
