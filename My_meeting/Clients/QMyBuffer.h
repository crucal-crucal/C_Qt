<<<<<<< HEAD
#ifndef QMYBUFFER_H
#define QMYBUFFER_H
//#define DEBUG

#include <QObject>
#include <QIODevice>
#include <QMutex>
#include <QBuffer>
#include <QDebug>

class QMyBuffer : public QIODevice
{
    Q_OBJECT
public:
    explicit QMyBuffer(QObject *parent = nullptr);

signals:
    void sendAudio(QByteArray);

    // QIODevice interface
protected:
    qint64 readData(char * data, qint64 maxSize);       //从设备读取数据到缓冲区
    qint64 writeData(const char * data, qint64 maxSize);//缓冲区数据写入设备
private:
    QBuffer myBuffer;
};

#endif // QMYBUFFER_H
=======
#ifndef QMYBUFFER_H
#define QMYBUFFER_H
//#define DEBUG

#include <QObject>
#include <QIODevice>
#include <QMutex>
#include <QBuffer>
#include <QDebug>

class QMyBuffer : public QIODevice
{
    Q_OBJECT
public:
    explicit QMyBuffer(QObject *parent = nullptr);

signals:
    void sendAudio(QByteArray);

    // QIODevice interface
protected:
    qint64 readData(char * data, qint64 maxSize);       //从设备读取数据到缓冲区
    qint64 writeData(const char * data, qint64 maxSize);//缓冲区数据写入设备
private:
    QBuffer myBuffer;
};

#endif // QMYBUFFER_H
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
