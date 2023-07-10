
#include "mainwindow.h"
#include "ui_mainwindow.h"

QString MainWindow::getLocalIP()
{
    //获取本机IPv4地址
    QString hostName = QHostInfo::localHostName();    //本地主机名
    QHostInfo hostInfo = QHostInfo::fromName(hostName);
    QString   localIP = "";

    QList<QHostAddress> addList=hostInfo.addresses();  //本机IP地址列表
    if (addList.isEmpty())
        return localIP;

    foreach(QHostAddress aHost, addList)
        if (QAbstractSocket::IPv4Protocol==aHost.protocol())
        {
            localIP=aHost.toString();
            break;
        }
    return localIP;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->port->setText("8989");
    //打印线程地址
    qDebug()<<"服务器主线程："<<QThread::currentThread();

    m_tcp = new QTcpServer(this);

    connect(m_tcp, &QTcpServer::newConnection, this, [=](){
        QTcpSocket *tcpSocket = m_tcp->nextPendingConnection();

        RecvFile *subThread = new RecvFile(tcpSocket);

        subThread->start();
        connect(subThread, &RecvFile::over, this, [=](){
            QMessageBox::information(this, "文件接收", "文件接收完毕！！");
            subThread->exit();
            subThread->wait();
            subThread->deleteLater();
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
//    qDebug()<<getLocalIP();
}

