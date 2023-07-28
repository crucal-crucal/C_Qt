
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("TCP");
    m_server = new QTcpServer(this);
    connect(m_server, &QTcpServer::newConnection, this, [&](){
        m_tcp = m_server->nextPendingConnection();
        ui->plainTextEdit->appendPlainText("accept connect");
        //检测客户端有连接
        connect(m_tcp, &QTcpSocket::readyRead, this, [&](){
            auto s = m_tcp->readAll();
            ui->plainTextEdit->appendPlainText("客户端："+s);
        });
        //客户端断开了连接
        connect(m_tcp, &QTcpSocket::disconnected, this, [&](){
           ui->plainTextEdit->appendPlainText("dis");
            m_tcp->deleteLater();
        });
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_StartServer_clicked()
{
    auto port = ui->lineEdit->text().toInt();
    //设置服务器监听
    m_server->listen(QHostAddress::Any, port);
}

