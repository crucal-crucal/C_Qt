
#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->labPic->setPixmap(QPixmap(":/images/d0.jpg"));

    pixmap.resize(6);
    for (int i=0;i<pixmap.size();i++)
    {
        QString s = QString(":/images/d%1.jpg").arg(i+1);
        pixmap[i] = new QPixmap(s);
    }

    mythread = new MyThread();
    connect(mythread, &MyThread::newValue, this, [&](int cnt1, int cnt2){
        QString s = QString("第 %1 次梭哈，点数为：%2").arg(cnt1).arg(cnt2);
        ui->plainTextEdit->appendPlainText(s);
        ui->labPic->setPixmap(*pixmap[cnt2-1]);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actThread_Run_triggered()
{
//    mythread->start();
    QThreadPool::globalInstance()->start(mythread);
    ui->actThread_Run->setEnabled(false);
    ui->actDice_Run->setEnabled(true);
    ui->actThread_Quit->setEnabled(true);
}


void MainWindow::on_actClear_triggered()
{
    ui->plainTextEdit->clear();
}


void MainWindow::on_actThread_Quit_triggered()
{
    mythread->m_stop = true;
    ui->actThread_Run->setEnabled(true);
    ui->actDice_Run->setEnabled(false);
    ui->actThread_Quit->setEnabled(false);
}


void MainWindow::on_actDice_Run_triggered()
{
    mythread->m_paused = false;
    ui->actDice_Pause->setEnabled(true);
    ui->actDice_Run->setEnabled(false);
}


void MainWindow::on_actDice_Pause_triggered()
{
    mythread->m_paused = true;
    ui->actDice_Pause->setEnabled(false);
    ui->actDice_Run->setEnabled(true);
}

