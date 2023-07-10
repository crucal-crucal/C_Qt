
#ifndef QMYSERVER_H
#define QMYSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>

#include "MyTcpServer.h"
#include "QMyThread.h"
/*@Brief 服务器 -- 数据中转
 * 1.处理客户端连接请求：主讲者模式，成员模式
 * 2.接收来自客户端的数据：a.客户端聊天，视频，图片
 * 3.向客户端发送或更新数据：a.文字 b.图片 c.视频 d.登录验证
 * importance:需采用并发处理
 **/
enum Mode
{
    host,//主讲人
    member//成员
    //@brief 区分谁是主讲人
};
class QMyServer : public QObject
{
    Q_OBJECT
public:
    explicit QMyServer(QObject *parent = nullptr);
    ~QMyServer();
public slots:
    void serverInit(); //初始化服务器
    void serverListen(unsigned short port); //服务器监听端口

private slots:

signals:
    void recvVideo(QByteArray);//接收客户端传来的视频
public:
    MyTcpServer* mytcpServer; //服务器
    QList<QTcpSocket*> myClients;//客户端请求
};

#endif // QMYSERVER_H
