<<<<<<< HEAD
<<<<<<< HEAD

#ifndef QMYCAMERATHREAD_H
#define QMYCAMERATHREAD_H

#include "QMyCamera.h"
#include "QMyShareDesktop.h"
#include <QObject>
#include <QThread>
/*brief
 * 此线程专门用作摄像机捕捉画面，桌面共享
 * 采集到的数据将以信号的形式发出
 * */
class QMyCameraThread : public QThread {
  Q_OBJECT
public:
  explicit QMyCameraThread(QObject *parent = nullptr);
  friend class MainWindow;

protected:
  void run() override;

private:
  QMyCamera *myCamera;
  QMyShareDesktop *shareDesktop;

signals:
  void forwardCameraPic(QImage);         // 转发摄像头捕捉的图片
  void forward_shareDesktopPic(QPixmap); // 转发共享桌面捕捉的图片
  void forward_sendServerDeskPic(QByteArray); // 转发要发送服务器的图片

  void stopShareDesktop();  // 再次转发信号
  void startShareDesktop(); // 再次转发信号
  void startCamera();       // 再次转发信号
  void stopCamera();        // 再次转发信号
};

#endif // QMYCAMERATHREAD_H
=======
=======
>>>>>>> 47b8f66 (update)

#ifndef QMYCAMERATHREAD_H
#define QMYCAMERATHREAD_H


#include <QObject>
#include <QThread>
#include "QMyCamera.h"
#include "QMyShareDesktop.h"
/*brief
 * 此线程专门用作摄像机捕捉画面，桌面共享
 * 采集到的数据将以信号的形式发出
 * */
class QMyCameraThread : public QThread
{
    Q_OBJECT
public:
    explicit QMyCameraThread(QObject *parent = nullptr);
    friend class MainWindow;

protected:
    void run() override;

private:
    QMyCamera *myCamera;
    QMyShareDesktop *shareDesktop;

signals:
    void forwardCameraPic(QImage);//转发摄像头捕捉的图片
    void forward_shareDesktopPic(QPixmap);//转发共享桌面捕捉的图片
    void forward_sendServerDeskPic(QByteArray);//转发要发送服务器的图片

    void stopShareDesktop();//再次转发信号
    void startShareDesktop();//再次转发信号
    void startCamera();//再次转发信号
    void stopCamera();//再次转发信号
};

#endif // QMYCAMERATHREAD_H
<<<<<<< HEAD
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
=======
>>>>>>> 47b8f66 (update)
