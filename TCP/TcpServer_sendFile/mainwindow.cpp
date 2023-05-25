
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->port->setText("8989");
    //打印线程地址
    qDebug()<<"服务器主线程："<<QThread::currentThread();

    m_tcp = new MyTcpServer(this);

    connect(m_tcp, &MyTcpServer::newDescriptor, this, [=](qintptr sock){
//        QTcpSocket *m_tcpsocket = m_tcp->nextPendingConnection();

        //创建线程对象
        RecvFile *subThread = new RecvFile(sock);
        subThread->start();

        connect(subThread, &RecvFile::over, this, [=](){
            QMessageBox::information(this, "文件接收", "文件接收完毕！！");
//            subThread->exit();
//            subThread->wait();
//            subThread->deleteLater();
        });
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_Setlisten_clicked()
{
    unsigned short port = ui->port->text().toUShort();
    m_tcp->listen(QHostAddress::Any, port);
}

