
#include "recvfile.h"

RecvFile::RecvFile(qintptr sock, QObject *parent)
    : QThread{parent}
{
    m_sock = sock;
}


void RecvFile::run()
{
    m_tcpSocket = new QTcpSocket(this);
    m_tcpSocket->setSocketDescriptor(m_sock);

    QFile *file = new QFile("Recv.txt");
    file->open(QFile::WriteOnly);

    //接受数据
    connect(m_tcpSocket, &QTcpSocket::readyRead, recvfile, [=](){
        //读取次数
        cnt = 0;
        //文件大小
        filesize = 0;
        if(!cnt)
        {
            m_tcpSocket->read((char*)&filesize, 4);
        }
        //读出剩余数据
        QByteArray all = m_tcpSocket->readAll();
        cnt += all.size();
        file->write(all);

        qDebug()<<"cnt:"<<cnt<<"\nfilesize"<<filesize;
        //接受完毕
        if(cnt == filesize)
        {
            qDebug()<<1;
            m_tcpSocket->close();
            m_tcpSocket->deleteLater();
            file->close();
            file->deleteLater();
            emit over();
        }
    });

    //进入事件循环,子线程进入后台，一直检测是否需要接收文件
    exec();
}

