
#ifndef SENDFILE_H
#define SENDFILE_H


#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QFile>
#include <QByteArray>
#include <QFileInfo>

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

};

#endif // SENDFILE_H
