
#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //线程池初始化，设置最大线程池数
    QThreadPool::globalInstance()->setMaxThreadCount(4);

    //添加任务
    MyWork *task = new MyWork();
    task->setAutoDelete(true);//执行完成自动删除该任务
    QThreadPool::globalInstance()->start(task);
}

MainWindow::~MainWindow()
{
    delete ui;
}


