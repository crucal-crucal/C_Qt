
#ifndef RECVFILE_H
#define RECVFILE_H


#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QFile>
#include <QFileInfo>
#include <QByteArray>
#include <QTcpServer>
#include <QTimer>
#include <QApplication>

class RecvFile : public QThread
{
    Q_OBJECT
public:
    explicit RecvFile(QTcpSocket *tcp, QObject *parent = nullptr);
    void deleteData();

signals:
    //接收进度
    void sigFileInfo(QString ,QString ,qint64 ,qint64 );
    //接收文件完毕
    void sigOver(QTcpSocket*,QString,bool);/*接收完毕，是否成功*/
    void over();

private slots:
    void dealReadyRead();
    void dealDisconnected();
    void dealTimeout();

private:
    void returnReceice(bool);  /*接收完毕，告诉发送端是否接收成功*/
    QString getFilePath(QString);/*文件名重复则重命名*/

protected:
    void run() override;

private:
    QTcpSocket *m_tcpSocket;
    QFile m_file;
    bool m_isStart;
    qint64 m_recSize;
    qint64 m_fileSize;
    QString m_filePath;
    QString m_fileName;
    bool m_dealOver;
    QTimer m_timer;
};

#endif // RECVFILE_H
