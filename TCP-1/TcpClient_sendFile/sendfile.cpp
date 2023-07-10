
#include "sendfile.h"

SendFile::SendFile(QObject *parent)
    : QObject{parent}
{

}


void SendFile::connectServer(unsigned short port, QString ip)
{
    m_tcpsocket = new QTcpSocket;
    m_tcpsocket->connectToHost(QHostAddress(ip), port);

    //发送连接成功信号给主线程
    connect(m_tcpsocket, &QTcpSocket::connected, this, &SendFile::connectSuc);
    //断开连接发送信号给主线程
    connect(m_tcpsocket, &QTcpSocket::disconnected, this, [=](){
        m_tcpsocket->close();
        m_tcpsocket->deleteLater();
        emit disConnect();
    });
}

void SendFile::sendFile(QString path)
{
    file.setFileName(path);
    QFileInfo info(path);
    int filesize = info.size();

    //打开方式
    file.open(QFile::ReadOnly);

    //一行一行的读
    while(!file.atEnd())
    {
        static int num{};
        if(!num)
        {
            m_tcpsocket->write((char*)&filesize, 4);
        }
        QByteArray line = file.readLine();
        num += line.size();
        int percent = (num * 100 / filesize);
        emit curPercent(percent);
        m_tcpsocket->write(line);
    }
}

