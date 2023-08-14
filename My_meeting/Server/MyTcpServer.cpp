<<<<<<< HEAD
<<<<<<< HEAD
#include "MyTcpServer.h"

MyTcpServer::MyTcpServer(QObject *parent) : QTcpServer{parent} {}
// 不能直接在子线程里使用主线程的通信的套接字对象
void MyTcpServer::incomingConnection(qintptr handle) { emit newClient(handle); }
=======
=======
>>>>>>> 47b8f66 (update)
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
<<<<<<< HEAD
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
=======
>>>>>>> 47b8f66 (update)
