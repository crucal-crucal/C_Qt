<<<<<<< HEAD

#ifndef SENDFILE_H
#define SENDFILE_H


#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QFile>
#include <QByteArray>
#include <QFileInfo>
#include <QVector>
#include <QApplication>

class SendFile : public QObject
{
    Q_OBJECT
public:
    explicit SendFile(QObject *parent = nullptr);

    //连接服务器
    void connectServer(unsigned short port, QString ip);

    //发送文件
    void sendFile(QString path);

signals:
    void connectSuc();//成功连接
    void disConnect();//断开连接
    void curPercent(int);//当前百分比
private:
    QTcpSocket *m_tcpsocket;
    QFile file;
};

#endif // SENDFILE_H
=======

#ifndef SENDFILE_H
#define SENDFILE_H


#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QFile>
#include <QByteArray>
#include <QFileInfo>
#include <QVector>
#include <QApplication>

class SendFile : public QObject
{
    Q_OBJECT
public:
    explicit SendFile(QObject *parent = nullptr);

    //连接服务器
    void connectServer(unsigned short port, QString ip);

    //发送文件
    void sendFile(QString path);

signals:
    void connectSuc();//成功连接
    void disConnect();//断开连接
    void curPercent(int);//当前百分比
private:
    QTcpSocket *m_tcpsocket;
    QFile file;
};

#endif // SENDFILE_H
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
