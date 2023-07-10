
#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QTcpSocket>
#include <QLabel>
#include <QRandomGenerator>
#include <QThread>
#include "QMyCameraThread.h"
#include "QMyClients.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void startCameraThread();//开启摄像头 --- 子线程
    void terminateCameraThread();//关闭摄像头 --- 子线程

public slots:
    void loadCameraPictrue(QImage img);//导入摄像头数据

private slots:
    void startCamera();//开启摄像头
    void startShareDesktop();//开启桌面共享
    void stopCamera();//关闭摄像头
    void stopShareDesktop();//关闭桌面共享
    void showSharePicToLabel(QPixmap map);//将桌面内容显示到界面（label）
    void setSendServerState();//是否开启将数据上传到服务器
    void sendAudio();//传递声音到服务器
    void sendMessage();//sendMessage

signals:
    void sendVedioToServer(QPixmap);
    void sendAudioToServer();//传递声音到服务器
    void sendMessageToServer(QString);//发送消息到服务器
    void sendUserMessgeToServer();//发送用户信息到服务器

private:
    Ui::MainWindow *ui;
    QMyCameraThread *cameraThread; // 子线程(处理摄像头和桌面共享)
    QMyClients *myClients;//客户端 --- 负责接收发送数据
    bool sendVedioState; // 是否开启传输视频到服务器
    QThread *clientsThread; //子线程

    // QWidget interface
protected:
   // void keyPressEvent(QKeyEvent *event);

};

#endif // MAINWINDOW_H
