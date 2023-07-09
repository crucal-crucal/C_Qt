#include "MyTcpServer.h"

MyTcpServer::MyTcpServer(QObject *parent)
    : QTcpServer{parent}
{

}
//不能直接在子线程里使用主线程的通信的套接字对象
void MyTcpServer::incomingConnection(qintptr handle)
{
    emit newClient(handle);
}
