<<<<<<< HEAD
#include "QMyIODevice.h"

QMyIODevice::QMyIODevice(QObject *parent) : QIODevice(parent) {
  this->timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, [=] {
    // 计时完成关闭录音设备，并且发出信号，传递数组
    //        closeMyIoDevice();
    emit sendAudioData(this->audioByteArray);
    this->audioByteArray.clear();
  });
  this->open(QIODeviceBase::WriteOnly); // 打开本设备
}

void QMyIODevice::startMyIoDevice() {
  this->timer->start(100); // 测试---需调
}

void QMyIODevice::closeMyIoDevice() {
  this->close(); // 关闭本IO设备R
  this->timer->stop();
}

void QMyIODevice::initMyIoDevice() { this->audioByteArray.clear(); }

qint64 QMyIODevice::readData(char *data, qint64 maxSize) {
  // 读数据，不做处理
  Q_UNUSED(data)
  Q_UNUSED(maxSize)
  return -1;
}

qint64 QMyIODevice::writeData(const char *data, qint64 maxSize) {
  // 写缓冲区的数据
  if (this->isOpen()) {
    this->audioByteArray.append(data);
  }
  // qDebug()<< static_cast<qint16>(*data);
  return maxSize;
}
=======
#include "QMyIODevice.h"

QMyIODevice::QMyIODevice(QObject *parent) : QIODevice(parent)
{
    this->timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [ = ]
    {
        //计时完成关闭录音设备，并且发出信号，传递数组
//        closeMyIoDevice();
        emit sendAudioData(this->audioByteArray);
        this->audioByteArray.clear();
    });
    this->open(QIODeviceBase::WriteOnly);   //打开本设备
}
void QMyIODevice::startMyIoDevice()
{
    this->timer->start(100);//测试---需调
}
void QMyIODevice::closeMyIoDevice()
{
    this->close();      //关闭本IO设备R
    this->timer->stop();
}
void QMyIODevice::initMyIoDevice()
{
    this->audioByteArray.clear();
}
qint64 QMyIODevice::readData(char * data, qint64 maxSize)
{
    //读数据，不做处理
    Q_UNUSED(data)
    Q_UNUSED(maxSize)
    return -1;
}
qint64 QMyIODevice::writeData(const char * data, qint64 maxSize)
{
    //写缓冲区的数据
    if (this->isOpen())
    {
        this->audioByteArray.append(data);
    }
    //qDebug()<< static_cast<qint16>(*data);
    return maxSize;
}
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
