<<<<<<< HEAD
#include "QMyBuffer.h"

QMyBuffer::QMyBuffer(QObject *parent)
    : QIODevice{parent}
{

}

qint64 QMyBuffer::readData(char * data, qint64 maxSize)
{
    //读数据，不做处理
    Q_UNUSED(data)
    Q_UNUSED(maxSize)
    return -1;
}

qint64 QMyBuffer::writeData(const char *data, qint64 maxSize)
{
#ifdef DEBUG
    qDebug() << "writeDate";
#endif
    //写缓冲区的数据
    myBuffer.open(QIODevice::ReadWrite);
    QMutex mutex;
    myBuffer.write(data, maxSize);
    QByteArray audioArray;
    {
        QMutexLocker locker(&mutex);//为其上锁，防止其他线程竞争，如果锁正在被使用则阻塞此线程。匿名函数执行完后自动释放锁
        audioArray = myBuffer.readAll();
    }
    emit sendAudio(audioArray);

    return maxSize;
}
=======
#include "QMyBuffer.h"

QMyBuffer::QMyBuffer(QObject *parent)
    : QIODevice{parent}
{

}

qint64 QMyBuffer::readData(char * data, qint64 maxSize)
{
    //读数据，不做处理
    Q_UNUSED(data)
    Q_UNUSED(maxSize)
    return -1;
}

qint64 QMyBuffer::writeData(const char *data, qint64 maxSize)
{
#ifdef DEBUG
    qDebug() << "writeDate";
#endif
    //写缓冲区的数据
    myBuffer.open(QIODevice::ReadWrite);
    QMutex mutex;
    myBuffer.write(data, maxSize);
    QByteArray audioArray;
    {
        QMutexLocker locker(&mutex);//为其上锁，防止其他线程竞争，如果锁正在被使用则阻塞此线程。匿名函数执行完后自动释放锁
        audioArray = myBuffer.readAll();
    }
    emit sendAudio(audioArray);

    return maxSize;
}
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
