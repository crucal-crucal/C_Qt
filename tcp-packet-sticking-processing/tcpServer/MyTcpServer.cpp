#include "MyTcpServer.h"

MyTcpServer::MyTcpServer(QObject *parent)
    : QTcpServer{parent}
{

}

void MyTcpServer::incomingConnection(qintptr handle)
{
    emit newClient(handle);
}
