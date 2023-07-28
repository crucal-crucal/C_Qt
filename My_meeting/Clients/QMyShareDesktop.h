<<<<<<< HEAD
#ifndef QMYSHAREDESKTOP_H
#define QMYSHAREDESKTOP_H

#include <QGuiApplication>
#include <QObject>
#include <QPixmap>
#include <QScreen>
#include <QTimer>

class QMyShareDesktop : public QObject {
  Q_OBJECT
public:
  explicit QMyShareDesktop(QObject *parent = nullptr);
  ~QMyShareDesktop();

  void setShareRate(int ms); /***无用函数******/
public slots:
  void startShareDesktop(); // 开启桌面共享
  void stopShareDesktop();  // 关闭桌面共享

private slots:
  void GetDesktopPictrue(); // 捕捉桌面画面
private:
  QScreen *screen; // 屏幕
  QTimer *timer;
  int rate; // 捕捉画面速度

signals:
  void finshed_LocalImportPictrue(QPixmap); // 捕捉到的画面显示到本地界面
  void finshed_sendToServer(QByteArray); // 捕捉到的画面给服务器
};

#endif // QMYSHAREDESKTOP_H
=======
#ifndef QMYSHAREDESKTOP_H
#define QMYSHAREDESKTOP_H

#include <QObject>
#include <QScreen>
#include <QPixmap>
#include <QGuiApplication>
#include <QTimer>

class QMyShareDesktop : public QObject
{
    Q_OBJECT
public:
    explicit QMyShareDesktop(QObject *parent = nullptr);
    ~QMyShareDesktop();

    void setShareRate(int ms);/***无用函数******/
public slots:
    void startShareDesktop();//开启桌面共享
    void stopShareDesktop();//关闭桌面共享

private slots:
    void GetDesktopPictrue();//捕捉桌面画面
private:
    QScreen *screen;//屏幕
    QTimer *timer;
    int rate;//捕捉画面速度

signals:
    void finshed_LocalImportPictrue(QPixmap);//捕捉到的画面显示到本地界面
    void finshed_sendToServer(QByteArray);//捕捉到的画面给服务器

};

#endif // QMYSHAREDESKTOP_H
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
