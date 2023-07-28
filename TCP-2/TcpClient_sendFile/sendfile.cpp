<<<<<<< HEAD
#include "sendfile.h"
#include <QDebug>
#include <QHostAddress>
#include <QApplication>
SendFile::SendFile(QObject *parent) : QObject(parent)
{
}

void SendFile::disConnectTcp()
{
    m_tcpSocket->disconnectFromHost();
}

void SendFile::connectServer(unsigned short port, QString ip)
{
    m_ip = ip;
    m_port = port;
    m_sendOk = false;
    m_tcpSocket = new QTcpSocket;
    m_tcpSocket->connectToHost(QHostAddress(m_ip), m_port);

    connect(m_tcpSocket, &QTcpSocket::connected, this, &SendFile::connectSuc);

    connect(m_tcpSocket, &QTcpSocket::disconnected, this, [=](){
        qDebug()<<"dealDisconnect";
        if(m_sendSize != m_fileSize)
        {
            qDebug()<<"中断！";
            m_stop = true;/*中途断开,就不发了*/
            emit sigOver(m_fileNameTime, false);
        }
        else if(!m_sendOk)
        {
            qDebug()<<"接收不成功！";
            emit sigOver(m_fileNameTime, false);/*接收没成功*/
        }
        else
        {
            emit sigOver(m_fileNameTime, true);
        }
    });
    connect(m_tcpSocket, &QTcpSocket::readyRead, this, [=](){
        qDebug()<<"dealRead";
        QTcpSocket* tcp = (QTcpSocket*)sender();
        char buf[1024] = {0};
        tcp->read(buf, 1024);
        QString flag = QString("%1").arg(buf);
        qDebug()<<"flag："<<flag;
        /*判断接收端是否接收成功*/
        if("Success" == flag)
        {
            m_sendOk = true;
        }
        else
        {
            m_sendOk = false;
        }
    });
}

void SendFile::sendFile(QString filePath)
{
    m_filePath = filePath.section("##",0,0);
    m_time = filePath.section("##",1,1);
    QFileInfo info(m_filePath);
    m_fileName = info.fileName();
    m_fileSize = info.size();
    QString msg = QString("%1##%2").arg(m_fileName).arg(m_fileSize);
    qDebug()<<"head:"<<msg;
    /*发送文件名和文件大小信息，*/
    m_tcpSocket->write(msg.toUtf8().data(), 1024);
    QApplication::processEvents();/*实时发送*/
    /*等待确定再发具体内容 发送文件*/

    m_fileNameTime = m_fileName + "##" + m_time;

    m_file.setFileName(m_filePath);
    qDebug()<<m_filePath;
    if(!m_file.open(QIODevice::ReadOnly)){
        return;
    }
    qint64 len = 0;
    m_sendSize = 0;
    m_stop = false;
    do{
        char buf[4*1024] = {0};
        len = m_file.read(buf,sizeof(buf));
        m_tcpSocket->write(buf,len);
        QApplication::processEvents();/*实时发送*/
//        msleep(10);/*发的太快，防止丢包*/
        _sleep(10);/*发的太快，防止丢包*/
        m_sendSize+=len;
        /*更新进度条*/
        if(len > 0)
            emit sigFileInfo(m_fileNameTime,m_sendSize);
    }while(len>0 && !m_stop);

    /*关闭文件*/
    m_file.close();
}
=======
#include "sendfile.h"
#include <QDebug>
#include <QHostAddress>
#include <QApplication>
SendFile::SendFile(QObject *parent) : QObject(parent)
{
}

void SendFile::disConnectTcp()
{
    m_tcpSocket->disconnectFromHost();
}

void SendFile::connectServer(unsigned short port, QString ip)
{
    m_ip = ip;
    m_port = port;
    m_sendOk = false;
    m_tcpSocket = new QTcpSocket;
    m_tcpSocket->connectToHost(QHostAddress(m_ip), m_port);

    connect(m_tcpSocket, &QTcpSocket::connected, this, &SendFile::connectSuc);

    connect(m_tcpSocket, &QTcpSocket::disconnected, this, [=](){
        qDebug()<<"dealDisconnect";
        if(m_sendSize != m_fileSize)
        {
            qDebug()<<"中断！";
            m_stop = true;/*中途断开,就不发了*/
            emit sigOver(m_fileNameTime, false);
        }
        else if(!m_sendOk)
        {
            qDebug()<<"接收不成功！";
            emit sigOver(m_fileNameTime, false);/*接收没成功*/
        }
        else
        {
            emit sigOver(m_fileNameTime, true);
        }
    });
    connect(m_tcpSocket, &QTcpSocket::readyRead, this, [=](){
        qDebug()<<"dealRead";
        QTcpSocket* tcp = (QTcpSocket*)sender();
        char buf[1024] = {0};
        tcp->read(buf, 1024);
        QString flag = QString("%1").arg(buf);
        qDebug()<<"flag："<<flag;
        /*判断接收端是否接收成功*/
        if("Success" == flag)
        {
            m_sendOk = true;
        }
        else
        {
            m_sendOk = false;
        }
    });
}

void SendFile::sendFile(QString filePath)
{
    m_filePath = filePath.section("##",0,0);
    m_time = filePath.section("##",1,1);
    QFileInfo info(m_filePath);
    m_fileName = info.fileName();
    m_fileSize = info.size();
    QString msg = QString("%1##%2").arg(m_fileName).arg(m_fileSize);
    qDebug()<<"head:"<<msg;
    /*发送文件名和文件大小信息，*/
    m_tcpSocket->write(msg.toUtf8().data(), 1024);
    QApplication::processEvents();/*实时发送*/
    /*等待确定再发具体内容 发送文件*/

    m_fileNameTime = m_fileName + "##" + m_time;

    m_file.setFileName(m_filePath);
    qDebug()<<m_filePath;
    if(!m_file.open(QIODevice::ReadOnly)){
        return;
    }
    qint64 len = 0;
    m_sendSize = 0;
    m_stop = false;
    do{
        char buf[4*1024] = {0};
        len = m_file.read(buf,sizeof(buf));
        m_tcpSocket->write(buf,len);
        QApplication::processEvents();/*实时发送*/
//        msleep(10);/*发的太快，防止丢包*/
        _sleep(10);/*发的太快，防止丢包*/
        m_sendSize+=len;
        /*更新进度条*/
        if(len > 0)
            emit sigFileInfo(m_fileNameTime,m_sendSize);
    }while(len>0 && !m_stop);

    /*关闭文件*/
    m_file.close();
}
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
