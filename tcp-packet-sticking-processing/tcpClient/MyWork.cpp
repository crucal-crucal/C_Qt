#include "MyWork.h"

MyWork::MyWork(QObject *parent)
    : QObject{parent}
{

}

void MyWork::connectToServer(QString ip, unsigned short port)
{
    qDebug() << "子线程的id：" << QThread::currentThread();
    //连接服务器
    m_tcp = new QTcpSocket;
    //非阻塞函数，调用了这个函数过后，并不一定表示客户端和服务器连接成功
    m_tcp->connectToHost(QHostAddress(ip), port);

    connect(m_tcp, &QTcpSocket::connected, this, &MyWork::connectOK);
    connect(m_tcp, &QTcpSocket::readyRead, this, [ = ]()
    {
//        QByteArray all = m_tcp->readAll();
//        emit messAge(all);
        dealData();
        m_tcp->close();
        m_tcp->deleteLater();
        emit gameOver();
    });
}

//拆包
void MyWork::dealData()
{
    //把包头的四个字节转化为整形过后，存储到totalBytes
    unsigned int totalBytes = 0;
    //存储当前已经接收的字节数
    unsigned int recvBytes = 0;
    QByteArray block;

    //判断有没有数据
    if (m_tcp->bytesAvailable() == 0)
    {
        qDebug() << "no data!";
        return;
    }
    //读包头,套接字缓存区里的数据
    //c++常量转换
    if (m_tcp->bytesAvailable() >= static_cast<qint64>(sizeof(int)))
    {
        //取出包头
        QByteArray head = m_tcp->read(sizeof(int));
        //head.data()得到的是char*，其实是一个地址，转化为int*过后还需要取值，所以加*
        //将大端数据转化为小端数据
        //totalBytes = qFromLittleEndian(*(int*)head.data());
        //c++强制类型转换(指针类型转换
        totalBytes = qFromLittleEndian(*reinterpret_cast<int*>(head.data()));
        //普通的PC机都是小端存储
        //如果是小端存储，小端转化为大端就使用 qToBigEndian，大端转化为小端就使用 qFromBigEndian
        //以上两个函数都是默认小端存储的主机上使用的,如果用到大端存储的主机上，是不工作的
        //如果是大端存储，小端转化为大端就使用 qFromLittleEndian，大端转化为小端就使用 qToLittleEndian
        //以上两个函数都是默认大端存储的主机上使用的,如果用到小端存储的主机上，是不工作的(不工作就是不会对数据做任何的转换
        qDebug() << "包头长度：" << totalBytes;
    }
    else
    {
        return;
    }
    //基于包头读数据块
    while (totalBytes - recvBytes > 0 && m_tcp->bytesAvailable())
    {
        block.append(m_tcp->read(totalBytes - recvBytes));
        recvBytes = block.size();
#ifdef DEBUG
        qDebug() << "totalBytes:  " << totalBytes;
        qDebug() << "recvBytes:   " << recvBytes;
#endif
    }
    //读完了
    if (totalBytes == recvBytes)
    {
        emit messAge(block);
    }

    //如果还有数据，继续读下一个数据包
    if (m_tcp->bytesAvailable() > 0)
    {
        qDebug() << "开始递归调用";
        dealData();
    }
}
