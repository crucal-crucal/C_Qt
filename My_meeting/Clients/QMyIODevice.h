<<<<<<< HEAD
#ifndef QMYIODEVICE_H
#define QMYIODEVICE_H
#include <QBuffer>
#include <QIODevice>
#include <QMutex>
#include <QTimer>

class QMyIODevice : public QIODevice {
  Q_OBJECT
public:
  QMyIODevice(QObject *parent = nullptr);
  void startMyIoDevice(); // 打开计时器，并写入音频文件
  void closeMyIoDevice(); // 关闭所有音频输入设备（包括计时器
  void initMyIoDevice();  // 初始化计时器音频存储数组
protected:
  qint64 readData(char *data, qint64 maxSize); // 从设备读取数据到缓冲区
  qint64 writeData(const char *data, qint64 maxSize); // 缓冲区数据写入设备
signals:
  void sendAudioData(QByteArray); // 发送音频数组
  void deviceIsClose();           // 暂时没用
private:
  QByteArray audioByteArray;
  QTimer *timer; // 计时器
};

#endif // TMYDEVICE_H
=======
#ifndef QMYIODEVICE_H
#define QMYIODEVICE_H
#include  <QIODevice>
#include <QBuffer>
#include <QTimer>
#include <QMutex>


class QMyIODevice : public QIODevice
{
    Q_OBJECT
public:
    QMyIODevice(QObject *parent = nullptr);
    void startMyIoDevice();//打开计时器，并写入音频文件
    void closeMyIoDevice();//关闭所有音频输入设备（包括计时器
    void initMyIoDevice();//初始化计时器音频存储数组
protected:
    qint64 readData(char * data, qint64 maxSize);       //从设备读取数据到缓冲区
    qint64 writeData(const char * data, qint64 maxSize);//缓冲区数据写入设备
signals:
    void sendAudioData(QByteArray);//发送音频数组
    void deviceIsClose();//暂时没用
private:
    QByteArray audioByteArray;
    QTimer *timer;//计时器
};

#endif // TMYDEVICE_H
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
