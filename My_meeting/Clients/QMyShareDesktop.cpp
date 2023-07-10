#include "QMyDataDecompression.h"
#include "QMyShareDesktop.h"

#include <QThread>

QMyShareDesktop::QMyShareDesktop(QObject *parent): QObject{parent}
{
    this->rate = 100;//默认100毫秒捕捉1张图片
    this->screen = QGuiApplication::primaryScreen();//获取屏幕指针
    this->timer = new QTimer(this);
    connect(this->timer, &QTimer::timeout, this, &QMyShareDesktop::GetDesktopPictrue); //定时捕捉
}
QMyShareDesktop::~QMyShareDesktop()
{

}
void QMyShareDesktop::startShareDesktop()
{
    if (!this->timer->isActive())
    {
        this->timer->start(this->rate);
    }
}
void QMyShareDesktop::stopShareDesktop()
{
    if (this->timer->isActive())
    {
        this->timer->stop();
    }
}
void QMyShareDesktop::setShareRate(int /*ms*/)
{
    //this->rate = 1000/ms;
}
void QMyShareDesktop::GetDesktopPictrue()
{
    static int ans  = 0;
    if (ans == 0)
    {
        ans++;
        qDebug() << "GetDesktopPictrue 所处线程:" << QThread::currentThread() << " - " << QThread::currentThreadId();
    }
    QPixmap map = screen->grabWindow(0);//获取一张桌面图片
    //map.scaled(800,480,Qt::KeepAspectRatio,Qt::FastTransformation).scaled(400,240,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    QByteArray byteArray = QMyDataDecompression::changedPixmapToByteArray(map);//静态成员函数，无需实例化即可调用
    emit finshed_sendToServer(byteArray);
    emit finshed_LocalImportPictrue(map);

}








