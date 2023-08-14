<<<<<<< HEAD
<<<<<<< HEAD

#include "QMyCameraThread.h"

QMyCameraThread::QMyCameraThread(QObject *parent) : QThread{parent} {}
void QMyCameraThread::run() {
  this->shareDesktop = new QMyShareDesktop(this);
  this->myCamera = new QMyCamera(this); // 创建摄像机对象
  qDebug() << "摄像头线程QMyCamera-线程地址:" << QThread::currentThread()
           << "  线程id:" << QThread::currentThreadId();
  connect(shareDesktop, &QMyShareDesktop::finshed_LocalImportPictrue, this,
          [=](QPixmap map) {
            emit this->forward_shareDesktopPic(map); // 将要上传到本地UI界面的
          });
  connect(shareDesktop, &QMyShareDesktop::finshed_sendToServer, this,
          [=](QByteArray byteArray) {
            emit this->forward_sendServerDeskPic(
                byteArray); // 将要发送给服务器的
          });
  connect(myCamera, &QMyCamera::currentPictrueChanged, this, [=](QImage img) {
    emit forwardCameraPic(img); // 把摄像头捕获的图片发出去
  });

  connect(this, &QMyCameraThread::stopCamera, myCamera,
          &QMyCamera::stopCamera); // 关闭摄像机
  connect(this, &QMyCameraThread::startCamera, myCamera,
          &QMyCamera::startCamera); // 开启摄像机
  connect(this, &QMyCameraThread::startShareDesktop, shareDesktop,
          &QMyShareDesktop::startShareDesktop); // 开启桌面共享
  connect(this, &QMyCameraThread::stopShareDesktop, shareDesktop,
          &QMyShareDesktop::stopShareDesktop); // 关闭桌面共享
  exec();                                      // 进入事件处理循环
}
=======
=======
>>>>>>> 47b8f66 (update)

#include "QMyCameraThread.h"

QMyCameraThread::QMyCameraThread(QObject *parent): QThread{parent}
{

}
void QMyCameraThread::run()
{
    this->shareDesktop = new QMyShareDesktop(this);
    this->myCamera = new QMyCamera(this);//创建摄像机对象
    qDebug() << "摄像头线程QMyCamera-线程地址:" << QThread::currentThread() << "  线程id:" << QThread::currentThreadId();
    connect(shareDesktop, &QMyShareDesktop::finshed_LocalImportPictrue, this, [ = ](QPixmap map)
    {
        emit this->forward_shareDesktopPic(map);//将要上传到本地UI界面的
    });
    connect(shareDesktop, &QMyShareDesktop::finshed_sendToServer, this, [ = ](QByteArray byteArray)
    {
        emit this->forward_sendServerDeskPic(byteArray);//将要发送给服务器的
    });
    connect(myCamera, &QMyCamera::currentPictrueChanged, this, [ = ](QImage img)
    {
        emit forwardCameraPic(img);//把摄像头捕获的图片发出去
    });
    
    connect(this, &QMyCameraThread::stopCamera, myCamera, &QMyCamera::stopCamera); //关闭摄像机
    connect(this, &QMyCameraThread::startCamera, myCamera, &QMyCamera::startCamera); //开启摄像机
    connect(this, &QMyCameraThread::startShareDesktop, shareDesktop, &QMyShareDesktop::startShareDesktop); //开启桌面共享
    connect(this, &QMyCameraThread::stopShareDesktop, shareDesktop, &QMyShareDesktop::stopShareDesktop); //关闭桌面共享
    exec();//进入事件处理循环
}
<<<<<<< HEAD
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
=======
>>>>>>> 47b8f66 (update)
