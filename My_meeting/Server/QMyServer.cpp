
#include "QMyServer.h"

QMyServer::QMyServer(QObject *parent): QObject{parent}
{
}

QMyServer::~QMyServer()
{

}

void QMyServer::serverInit()
{
    mytcpServer = new MyTcpServer(this);
    connect(mytcpServer, &MyTcpServer::newClient, this, [&](qintptr socket)
    {
        //处理子线程相关的动作
        QThread* subThread = new QThread;
        QMyThread* worker = new QMyThread(socket); //当前线程（子线程
        worker->moveToThread(subThread);//将子线程移动到工作线程
        worker->working();//工作函数
        /*客户端连接，要接收文件了*/
//        myClients.emplace_back(tcpSocket);
        connect(worker, &QMyThread::recvVideo, this, [&](QByteArray array)
        {
            emit recvVideo(array);
        });
        subThread->start(); //开启线程
    });
}

void QMyServer::serverListen(unsigned short port)
{
    mytcpServer->listen(QHostAddress::Any, port);
    if (mytcpServer->isListening())
        QMessageBox::information(nullptr, "listen", "successful!");
}


