#ifndef MYWORK_H
#define MYWORK_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QThread>
#include <QDebug>
#include <QtEndian>

class MyWork : public QObject
{
    Q_OBJECT
public:
    explicit MyWork(QObject *parent = nullptr);

    //连接服务器
    void connectToServer(QString ip, unsigned short port);
    //处理数据
    void dealData();
signals:
    //连接成功
    void connectOK();
    //发送接收到的数据给主线程
    void messAge(QByteArray msg);
    //传输完毕，关闭线程
    void gameOver();
private:
    QTcpSocket* m_tcp;
};

#endif // MYWORK_H
