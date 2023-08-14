<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 47b8f66 (update)
#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QFile>
#include <QFileInfo>
class SendFile : public QObject
{
    Q_OBJECT
public:
    explicit SendFile(QObject *parent = nullptr);
    void disConnectTcp();

    //连接服务器
    void connectServer(unsigned short port, QString ip);

    void sendHead();
    void sendFile(QString filePath);

signals:
    void sigFileInfo(QString ,qint64 );
    void sigOver(QString,bool);
    void dealDisconnect();
    void connectSuc();//成功连接
    void dealRead();
private:
    QString m_ip;
    ushort m_port;
    QTcpSocket* m_tcpSocket;

    QFile m_file;
    qint64 m_fileSize;
    qint64 m_sendSize;
    QString m_filePath;
    QString m_fileName;
    bool m_stop;
    bool m_sendOk;
    QString m_time;
    QString m_fileNameTime;

};

#endif // CLIENTTHREAD_H
<<<<<<< HEAD
=======
#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QFile>
#include <QFileInfo>
class SendFile : public QObject
{
    Q_OBJECT
public:
    explicit SendFile(QObject *parent = nullptr);
    void disConnectTcp();

    //连接服务器
    void connectServer(unsigned short port, QString ip);

    void sendHead();
    void sendFile(QString filePath);

signals:
    void sigFileInfo(QString ,qint64 );
    void sigOver(QString,bool);
    void dealDisconnect();
    void connectSuc();//成功连接
    void dealRead();
private:
    QString m_ip;
    ushort m_port;
    QTcpSocket* m_tcpSocket;

    QFile m_file;
    qint64 m_fileSize;
    qint64 m_sendSize;
    QString m_filePath;
    QString m_fileName;
    bool m_stop;
    bool m_sendOk;
    QString m_time;
    QString m_fileNameTime;

};

#endif // CLIENTTHREAD_H
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
=======
>>>>>>> 47b8f66 (update)
