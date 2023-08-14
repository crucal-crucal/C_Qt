<<<<<<< HEAD
<<<<<<< HEAD

#include "QMyThread.h"

QMyThread::QMyThread(qintptr socket, QObject *parent) : QObject{parent} {
  m_socket = socket;
  //    this->setAutoDelete(false);
}

QMyThread::~QMyThread() {}

void QMyThread::working() {
#ifdef NDEUBG
  qDebug() << "now id : " << QThread::currentThread();
#endif
  mytcpSocket =
      new QTcpSocket; // 不能在构造函数里实例化，因为构造函数里是主线程在操作
  mytcpSocket->setSocketDescriptor(m_socket); // 设置好之后，就可以通信了
  // 接收图像
  connect(mytcpSocket, &QTcpSocket::readyRead, this, [&]() {
    qDebug() << "readRead!";
    dealread();
  });
}

// 处理信息
void QMyThread::dealread() {
  // 传输图像
  emit recvVideo(mytcpSocket->readAll());
}

// void QMyThread::run()
//{
// #ifdef NDEBUG
//     qDebug() << "run:";
// #endif
//     //接收图像
//     connect(mytcpSocket, &QTcpSocket::readyRead, this, [&]()
//     {
//         /*接收文件*/
//         emit recvVideo(mytcpSocket->readAll());
//     });

////    mytcpServer = new QMyServer(this);

////    //检测到新的连接，创建一个套接字
////    connect(mytcpServer, &QMyServer::newDescriptor, this, [&](qintptr sock){
////        //        QMyThread* myThread = new QMyThread(sock);
////        QTcpSocket* mytcpSocket = new QTcpSocket(this);

////        mytcpSocket->setSocketDescriptor(sock); //设置当前套接字
////        mytcpServer->myClients.emplace_back(mytcpSocket);//加入队列

////        //接收图像
////        connect(mytcpSocket, &QTcpSocket::readyRead, this, [&](){
////            /*接收文件*/
////            emit recvVideo(mytcpSocket->readAll());
////        });
////    });

//    exec();//线程循环
//}
=======
=======
>>>>>>> 47b8f66 (update)

#include "QMyThread.h"

QMyThread::QMyThread(qintptr socket, QObject *parent): QObject{parent}
{
    m_socket = socket;
}

QMyThread::~QMyThread()
{

}

void QMyThread::working()
{
#ifdef NDEUBG
    qDebug() << "now id : " << QThread::currentThread();
#endif
    mytcpSocket = new QTcpSocket;//不能在构造函数里实例化，因为构造函数里是主线程在操作
    mytcpSocket->setSocketDescriptor(m_socket);//设置好之后，就可以通信了
    //接收图像
    connect(mytcpSocket, &QTcpSocket::readyRead, this, [&]()
    {
        qDebug() << "readRead!";
        dealread();
    });
}

//处理信息
void QMyThread::dealread()
{
    //传输图像
    emit recvVideo(mytcpSocket->readAll());
}

//void QMyThread::run()
//{
//#ifdef NDEBUG
//    qDebug() << "run:";
//#endif
//    //接收图像
//    connect(mytcpSocket, &QTcpSocket::readyRead, this, [&]()
//    {
//        /*接收文件*/
//        emit recvVideo(mytcpSocket->readAll());
//    });

////    mytcpServer = new QMyServer(this);

////    //检测到新的连接，创建一个套接字
////    connect(mytcpServer, &QMyServer::newDescriptor, this, [&](qintptr sock){
////        //        QMyThread* myThread = new QMyThread(sock);
////        QTcpSocket* mytcpSocket = new QTcpSocket(this);

////        mytcpSocket->setSocketDescriptor(sock); //设置当前套接字
////        mytcpServer->myClients.emplace_back(mytcpSocket);//加入队列

////        //接收图像
////        connect(mytcpSocket, &QTcpSocket::readyRead, this, [&](){
////            /*接收文件*/
////            emit recvVideo(mytcpSocket->readAll());
////        });
////    });

//    exec();//线程循环
//}

<<<<<<< HEAD
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
=======
>>>>>>> 47b8f66 (update)
