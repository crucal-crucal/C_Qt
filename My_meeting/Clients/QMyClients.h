
#ifndef QMYCLIENTS_H
#define QMYCLIENTS_H


#include <QObject>
#include <QTcpSocket>
#include <QMessageBox>
#include <QInputDialog>
#include <mutex>
#include <QHostInfo>
#include <QMutex>
#include <queue>

#include "QMyDataDecompression.h"
#include "QMyAudio.h"


/*@brief  客户端
 * 1.向服务器申请连接
 * 2.发送数据(先发送给服务器->目的客户端)
 * 3.接收数据(来自其他客户端的数据->服务器->本地客户端)
 * 5.接收来自摄像机类QMyCamera的数据 --- 发送到服务器
 * */
 //------------------------------测试数据接收转发时无需看此步骤----------------------------------------------
 /*brief
  * 当要发送数据给服务器时需先使用协议将其封装成一个协议包，最后发送这个数据的字节包到服务器
  * QMyDataDecompression 需使用此类进行数据的封装并转换为字节
  * 最后将字节发送给服务器，服务器再根据协议进行解析转发
  * */
//#define DEBUG
class QMyClients : public QObject
{
    Q_OBJECT
public:
    QString getLocalIP();
    explicit QMyClients(QObject *parent = nullptr);
    ~QMyClients();

public slots:
    void connectToServer();//连接服务器后向服务器发送一次信息
    void sendVideoToServer(QPixmap map);//发送视频数据到服务器
    void sendUserMessgeToServer();//发送用户信息到服务器
    void sendAudiotoServer();//发送音频信息给服务器
    void sendMessageToSever(QString text);
    void sendDeskTopToServer(QByteArray target_data);
private slots:
    void ReadAllData();//读取服务器发送的数据包

signals:

private:
    std::mutex _mutex;//互斥锁，防止多个线程竞争同一资源
    QTcpSocket *tcpSocket;
    QMyDataDecompression *decompression;//对数据进行打包和解析
    QMyAudio* myAudio; //音频组件
    std::queue<QByteArray> receiveBuffer;//接收缓存队列
};

#endif // QMYCLIENTS_H
/*
 *  QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << messageLineEdit->text();

    tcpSocket->write(block);
    tcpSocket->flush();
 *
 * */
