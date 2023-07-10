#include "QMyAudio.h"

QMyAudio::QMyAudio(QObject *parent)
    : QObject{parent}
{
//    device = QMediaDevices::defaultAudioInput();  //默认音频输入设备
//    if (device.isNull())
//    {
//        QMessageBox::information(nullptr, "提示", "无音频输入设备");
//        return;
//    }

//    //首选音频格式
//    audioFormat = device.preferredFormat();     //音频输入设备的首选音频格式

//    //“开始采集”按钮
//    int index = audioFormat.sampleFormat();
//    if (!index)
//    {
//        QMessageBox::critical(nullptr, "错误", "请设置采样点格式");
//        return;
//    }
      myIODevice = new QMyIODevice(this);
}

void QMyAudio::startMyAudio()
{
    //“开始采集”按钮
    myIODevice->startMyIoDevice();
    // connect(myDevice,&QMyIODevice::updateBlockSize,this, &MainWindow::do_IODevice_update);
    audioSource->start(myIODevice); //以流设备作为参数，开始录入音频输入数据
}

void QMyAudio::initMyAudio()
{
//    QAudioFormat daqFormat;   //设置音频格式
//    daqFormat.setSampleRate(audioFormat.sampleRate());      //采样频率
//    daqFormat.setChannelCount(audioFormat.channelCount());   //通道个数
//    int index = audioFormat.sampleFormat();
//    daqFormat.setSampleFormat(QAudioFormat::SampleFormat(index));  //采样点格式

//    QAudioSource *audioSource = new QAudioSource(daqFormat, nullptr);
//    audioSource->setBufferSize(10000);
//    audioSource->setVolume(1);
    QAudioFormat daqFormat;
    daqFormat.setSampleRate(48000);      //采样频率
    daqFormat.setChannelCount(1);   //通道个数
    daqFormat.setSampleFormat(QAudioFormat::UInt8);  //采样点格式
    audioSource = new QAudioSource(daqFormat, this);
    audioSource->setBufferSize(1000000);    //设置缓冲区大小,如10000
    audioSource->setVolume(1);                   //设置录音音量， 0~1

    QAudioDevice device = QMediaDevices::defaultAudioInput(); //默认音频输入设备
    if (device.isNull())
    {
        QMessageBox::information(nullptr, "提示", "无音频输入设备");
        return;
    }
   
}

void QMyAudio::stopMyAudio()
{
    this->audioSource->stop();//暂停录音
}


