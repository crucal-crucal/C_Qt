
#ifndef RECVFILE_H
#define RECVFILE_H


#include <QThread>
#include <QTcpSocket>
#include <QFile>
#include <QFileInfo>
#include <QByteArray>

class RecvFile : public QThread
{
    Q_OBJECT
public:
    explicit RecvFile(qintptr sock, QObject *parent = nullptr);

signals:
    //接收文件完毕
    void over();

    // QThread interface
protected:
    void run();

private:
    QTcpSocket *m_tcpSocket;
    qintptr m_sock;
    RecvFile *recvfile;
    int cnt, filesize;
};

#endif // RECVFILE_H
