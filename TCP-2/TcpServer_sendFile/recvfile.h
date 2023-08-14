<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 47b8f66 (update)
#ifndef SERVERTHEAD_H
#define SERVERTHEAD_H

#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QTimer>
#include <QMessageBox>

class RecvFile : public QThread
{
    Q_OBJECT
public:
    explicit RecvFile(QTcpSocket* qtcpSocket,QObject *parent = nullptr);
    void deleteData();
protected:
    virtual void run();
signals:
    void sigFileInfo(QString, qint64, qint64);/*接收进度*/
    void sigOver(QTcpSocket*, QString, bool);/*接收完毕，是否成功*/
private slots:
    void dealReadyRead();
    void dealDisconnected();
    void dealTimeout();
private:
    void returnReceice(bool);  /*接收完毕，告诉发送端是否接收成功*/
    QString getFileName(QString);/*文件名重复则重命名*/
private:
    QTcpSocket* m_qtcpSocket;
    QFile m_file;
    bool m_isStart;
    qint64 m_recSize;
    qint64 m_fileSize;
    QString m_filePath;
    QString m_fileName;
    bool m_dealOver;
    QTimer m_timer;
    int cnt{};
};

#endif // SERVERTHEAD_H
<<<<<<< HEAD
=======
#ifndef SERVERTHEAD_H
#define SERVERTHEAD_H

#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QTimer>
#include <QMessageBox>

class RecvFile : public QThread
{
    Q_OBJECT
public:
    explicit RecvFile(QTcpSocket* qtcpSocket,QObject *parent = nullptr);
    void deleteData();
protected:
    virtual void run();
signals:
    void sigFileInfo(QString, qint64, qint64);/*接收进度*/
    void sigOver(QTcpSocket*, QString, bool);/*接收完毕，是否成功*/
private slots:
    void dealReadyRead();
    void dealDisconnected();
    void dealTimeout();
private:
    void returnReceice(bool);  /*接收完毕，告诉发送端是否接收成功*/
    QString getFileName(QString);/*文件名重复则重命名*/
private:
    QTcpSocket* m_qtcpSocket;
    QFile m_file;
    bool m_isStart;
    qint64 m_recSize;
    qint64 m_fileSize;
    QString m_filePath;
    QString m_fileName;
    bool m_dealOver;
    QTimer m_timer;
    int cnt{};
};

#endif // SERVERTHEAD_H
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
=======
>>>>>>> 47b8f66 (update)
