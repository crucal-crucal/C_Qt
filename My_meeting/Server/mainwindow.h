
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//#define NDEBUG
#include <QMainWindow>
#include <QLabel>
#include <QMessageBox>
#include <QImage>
#include <QAudioSink>
#include <QRandomGenerator>

#include "QMyServer.h"
#include "QMyDataDecompression.h"
/*@Brief 更新数据
 * */
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

private slots:
    void showPicturetoUI(QByteArray array);//在UI上显示图像
    void showAudiotoUI(QByteArray array);//在UI上开启音频
    void Listening_port();//监听端口
    void showPicture(QByteArray array);//显示图像
    void showText(QString text);
    void showVideo(QByteArray video, QByteArray audio);//开启音视频
signals:


private:
    Ui::MainWindow *ui;
    QMyServer* myServer; //服务器
    QAudioSink* audioSink;//播放音频组件
    QMyDataDecompression* myDataDecompression;//自定义协议
};

#endif // MAINWINDOW_H
