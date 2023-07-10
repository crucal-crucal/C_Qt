#ifndef QMYAUDIO_H
#define QMYAUDIO_H

#include <QObject>
#include <QtMultimedia>
#include <QMessageBox>
#include "QMyIODevice.h"

class QMyAudio : public QObject
{
    Q_OBJECT
public:
    explicit QMyAudio(QObject *parent = nullptr);
    void startMyAudio();//开始录音
    void initMyAudio();//初始化录音（输入设备
    void stopMyAudio();//暂停录音
signals:
    void sendAudio(QByteArray);

public:
    QAudioDevice device;      //默认音频输入设备
    QAudioSource* audioSource; //录入音频组件
    QMyIODevice *myIODevice; //输入输出流
};

#endif // QMYAUDIO_H
