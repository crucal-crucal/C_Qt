
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

    work = new MyWork();
    connect(work, &MyWork::newValue, this, [&](int cnt1, int cnt2){
        QString s = QString("第 %1 次梭哈，点数为：%2").arg(cnt1).arg(cnt2);
                        ui->plainTextEdit->appendPlainText(s);
        ui->labPic->setPixmap(*pixmap[cnt2-1]);
    });

    connect(ui->actThread_Run, &QAction::triggered, this, &MainWindow::on_actThread_Run_triggered);
    connect(ui->actClear, &QAction::triggered, this, &MainWindow::on_actClear_triggered);
    connect(ui->actThread_Quit, &QAction::triggered, this, &MainWindow::on_actThread_Quit_triggered);
    connect(ui->actDice_Run, &QAction::triggered, this, &MainWindow::on_actDice_Run_triggered);
    connect(ui->actDice_Pause, &QAction::triggered, this, &MainWindow::on_actDice_Pause_triggered);
}

MainWindow::~MainWindow()
{
    delete ui;
}


//开启线程按钮
void MainWindow::on_actThread_Run_triggered()
{
    //    mythread->start();
    qDebug()<<"current Thread:\t"<<QThread::currentThread();
    QThreadPool::globalInstance()->start(work);
    ui->actThread_Run->setEnabled(false);
    ui->actDice_Run->setEnabled(true);
    ui->actThread_Quit->setEnabled(true);
}

//清空按钮
void MainWindow::on_actClear_triggered()
{
    ui->plainTextEdit->clear();
}

//结束线程按钮
void MainWindow::on_actThread_Quit_triggered()
{
    work->m_stop = true;
    ui->actThread_Run->setEnabled(true);
    ui->actDice_Run->setEnabled(false);
    ui->actThread_Quit->setEnabled(false);
}

//开始按钮
void MainWindow::on_actDice_Run_triggered()
{
    work->m_paused = false;
    ui->actDice_Pause->setEnabled(true);
    ui->actDice_Run->setEnabled(false);
}

//暂停按钮
void MainWindow::on_actDice_Pause_triggered()
{
    work->m_paused = true;
    ui->actDice_Pause->setEnabled(false);
    ui->actDice_Run->setEnabled(true);
}

