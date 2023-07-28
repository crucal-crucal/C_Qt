<<<<<<< HEAD
#include "recvfile.h"
#include <QDebug>
#include <QStringList>
#include <QApplication>
#include <QDateTime>
#include <QFileInfo>
#include <QDir>
RecvFile::RecvFile(QTcpSocket* qtcpSocket,QObject *parent) : QThread(parent)
{
    m_qtcpSocket = qtcpSocket;
    m_filePath = "";
    m_isStart = true;
    m_recSize = 0;
    m_dealOver = false;
}

void RecvFile::run()
{
    qDebug()<<"run:";
    connect(&m_timer, &QTimer::timeout, this, &RecvFile::dealTimeout);
    connect(m_qtcpSocket, &QTcpSocket::readyRead, this, &RecvFile::dealReadyRead);
    connect(m_qtcpSocket, &QTcpSocket::disconnected, this, &RecvFile::dealDisconnected);

    exec();/*进入事件循环*/
}

void RecvFile::dealReadyRead()
{
    //    qDebug()<<"ServerThread dealReadyRead:";
    if(m_isStart)
    {
        /*先接收文件名和文件大小信息*/
        m_isStart = false;
        char buf[4*1024] = {0};
        m_qtcpSocket->read(buf,1024);
        qDebug()<<"buf:"<<buf;
        /*其它连接*/
        QStringList list = QString("%1").arg(buf).split("##");
        if(list.length()<2)
        {
            emit sigOver(m_qtcpSocket,m_fileName,false);
        }
        m_fileName = QString("%1").arg(buf).section("##",0,0);
        m_fileSize = QString("%1").arg(buf).section("##",1,1).toInt();

        QString filePath = m_filePath + m_fileName;
        filePath = getFileName(filePath);/*名字去重*/
        QFileInfo info(filePath);
        m_fileName = info.fileName();

        //        qDebug()<<"m_fileName:"<<m_fileName<<"m_fileSize:"<<m_fileSize;
        m_file.setFileName(filePath);
        bool isOk = m_file.open(QIODevice::WriteOnly);
        if(!isOk)
        {
            qDebug()<<"open error!";
            returnReceice(false);
        }
        /*在文件名后加时间，区别*/
        QString current_date = QDateTime::currentDateTime().toString("MMddhhmmsszzz");

        qDebug()<<"time:"<<current_date;
        m_fileName = m_fileName + "##" + current_date;
        m_timer.start(1000);
    }
    /*接收文件*/
    QByteArray array = m_qtcpSocket->readAll();
    qint64 len = m_file.write(array);
    m_recSize += len;
    //    qDebug()<<m_recSize<<"/"<<m_fileSize;
    /*更新接收大小*/
    if(len>0)
    {
        emit sigFileInfo(m_fileName, m_fileSize, m_recSize);
    }
    if(m_recSize == m_fileSize)
    {
        qDebug()<<"rec sucess!";
        returnReceice(true);
    }

    return;
}

void RecvFile::dealDisconnected()
{
    qDebug()<<"dealDisconnected!";
    if(!m_dealOver)
    {
        if(m_fileSize != m_recSize)
        {
            emit sigOver(m_qtcpSocket, m_fileName, false);
        }
        else
        {
            emit sigOver(m_qtcpSocket, m_fileName, true);
        }
    }

    return;
}
//
void RecvFile::dealTimeout()
{
    static qint64 preSize =0;
    qDebug()<<this<<":"<<preSize<<":"<<m_recSize;
    if(preSize == m_recSize)
    {
        returnReceice(false);
    }
    preSize = m_recSize;

    return;
}
//释放内存
void RecvFile::deleteData()
{
    if(m_file.isOpen())
    {
        m_file.close();
    }
    if(m_qtcpSocket)
    {
        m_qtcpSocket->disconnectFromHost();
        m_qtcpSocket->close();
        m_qtcpSocket->deleteLater();
        m_qtcpSocket = nullptr;
    }
    //计时器检测进度
    if(m_timer.isActive())
        m_timer.stop();

    return;
}

//检测是否传输完成
void RecvFile::returnReceice(bool bl)
{
    qDebug()<<"returnReceice:"<<bl;
    m_dealOver = true;

    /*回复客户端是否接收成功！*/
    QString tranState{};//传输状态
    bool op{};//接收成功与否

    if(bl || m_fileSize == m_recSize)
        tranState = "Success", op = true;
    else
        tranState = "Error", op = false;

    QApplication::processEvents();/*实时发送*/
    m_qtcpSocket->write(QString(tranState).toUtf8().data(), 1024);
    emit sigOver(m_qtcpSocket, m_fileName, op);
    return;
}

//获取文件名
QString RecvFile::getFileName(QString filePath)
{
    /*判断文件名是否重复，重复则重命名*/
    QFile file(filePath);
    QFileInfo info(filePath);
    if(file.exists())
    {
        QString baseName = info.completeBaseName();
        return getFileName(m_filePath + baseName + QString("(%1).").arg(++cnt) + info.completeSuffix());
    }
    return filePath;
}

=======
#include "recvfile.h"
#include <QDebug>
#include <QStringList>
#include <QApplication>
#include <QDateTime>
#include <QFileInfo>
#include <QDir>
RecvFile::RecvFile(QTcpSocket* qtcpSocket,QObject *parent) : QThread(parent)
{
    m_qtcpSocket = qtcpSocket;
    m_filePath = "";
    m_isStart = true;
    m_recSize = 0;
    m_dealOver = false;
}

void RecvFile::run()
{
    qDebug()<<"run:";
    connect(&m_timer, &QTimer::timeout, this, &RecvFile::dealTimeout);
    connect(m_qtcpSocket, &QTcpSocket::readyRead, this, &RecvFile::dealReadyRead);
    connect(m_qtcpSocket, &QTcpSocket::disconnected, this, &RecvFile::dealDisconnected);

    exec();/*进入事件循环*/
}

void RecvFile::dealReadyRead()
{
    //    qDebug()<<"ServerThread dealReadyRead:";
    if(m_isStart)
    {
        /*先接收文件名和文件大小信息*/
        m_isStart = false;
        char buf[4*1024] = {0};
        m_qtcpSocket->read(buf,1024);
        qDebug()<<"buf:"<<buf;
        /*其它连接*/
        QStringList list = QString("%1").arg(buf).split("##");
        if(list.length()<2)
        {
            emit sigOver(m_qtcpSocket,m_fileName,false);
        }
        m_fileName = QString("%1").arg(buf).section("##",0,0);
        m_fileSize = QString("%1").arg(buf).section("##",1,1).toInt();

        QString filePath = m_filePath + m_fileName;
        filePath = getFileName(filePath);/*名字去重*/
        QFileInfo info(filePath);
        m_fileName = info.fileName();

        //        qDebug()<<"m_fileName:"<<m_fileName<<"m_fileSize:"<<m_fileSize;
        m_file.setFileName(filePath);
        bool isOk = m_file.open(QIODevice::WriteOnly);
        if(!isOk)
        {
            qDebug()<<"open error!";
            returnReceice(false);
        }
        /*在文件名后加时间，区别*/
        QString current_date = QDateTime::currentDateTime().toString("MMddhhmmsszzz");

        qDebug()<<"time:"<<current_date;
        m_fileName = m_fileName + "##" + current_date;
        m_timer.start(1000);
    }
    /*接收文件*/
    QByteArray array = m_qtcpSocket->readAll();
    qint64 len = m_file.write(array);
    m_recSize += len;
    //    qDebug()<<m_recSize<<"/"<<m_fileSize;
    /*更新接收大小*/
    if(len>0)
    {
        emit sigFileInfo(m_fileName, m_fileSize, m_recSize);
    }
    if(m_recSize == m_fileSize)
    {
        qDebug()<<"rec sucess!";
        returnReceice(true);
    }

    return;
}

void RecvFile::dealDisconnected()
{
    qDebug()<<"dealDisconnected!";
    if(!m_dealOver)
    {
        if(m_fileSize != m_recSize)
        {
            emit sigOver(m_qtcpSocket, m_fileName, false);
        }
        else
        {
            emit sigOver(m_qtcpSocket, m_fileName, true);
        }
    }

    return;
}
//
void RecvFile::dealTimeout()
{
    static qint64 preSize =0;
    qDebug()<<this<<":"<<preSize<<":"<<m_recSize;
    if(preSize == m_recSize)
    {
        returnReceice(false);
    }
    preSize = m_recSize;

    return;
}
//释放内存
void RecvFile::deleteData()
{
    if(m_file.isOpen())
    {
        m_file.close();
    }
    if(m_qtcpSocket)
    {
        m_qtcpSocket->disconnectFromHost();
        m_qtcpSocket->close();
        m_qtcpSocket->deleteLater();
        m_qtcpSocket = nullptr;
    }
    //计时器检测进度
    if(m_timer.isActive())
        m_timer.stop();

    return;
}

//检测是否传输完成
void RecvFile::returnReceice(bool bl)
{
    qDebug()<<"returnReceice:"<<bl;
    m_dealOver = true;

    /*回复客户端是否接收成功！*/
    QString tranState{};//传输状态
    bool op{};//接收成功与否

    if(bl || m_fileSize == m_recSize)
        tranState = "Success", op = true;
    else
        tranState = "Error", op = false;

    QApplication::processEvents();/*实时发送*/
    m_qtcpSocket->write(QString(tranState).toUtf8().data(), 1024);
    emit sigOver(m_qtcpSocket, m_fileName, op);
    return;
}

//获取文件名
QString RecvFile::getFileName(QString filePath)
{
    /*判断文件名是否重复，重复则重命名*/
    QFile file(filePath);
    QFileInfo info(filePath);
    if(file.exists())
    {
        QString baseName = info.completeBaseName();
        return getFileName(m_filePath + baseName + QString("(%1).").arg(++cnt) + info.completeSuffix());
    }
    return filePath;
}

>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
