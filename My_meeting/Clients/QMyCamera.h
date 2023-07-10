
#ifndef QMYCAMERA_H
#define QMYCAMERA_H


#include <QCamera>
#include <QtMultimedia>
#include <QMessageBox>
/*@brief 摄像机类
 * 1.采集图片
 * 2.向QMyClients对象发送采集的图片
 * 3.对图片进行处理(美化，压缩)
 * */
//namespace  farme {
//int width = 400;
//int height = 400;

//};
class QMyCamera : public QObject
{
    Q_OBJECT
public:
    explicit QMyCamera(QObject *parent = nullptr);
    ~QMyCamera();
    void setCameraRate(int ms = 100);//设置摄像头的帧率，默认30ms,1秒 = 1000ms,1秒大概抓30张(1000/30)

public slots:
    void startCamera();//开启摄像头
    void stopCamera();//关闭摄像头

private slots:
    void getImage(int id, const QImage &preview);//当抓取摄像头一张图片后，对其转换为QImage类型用信号发出去
    void catchCamera();//捕获摄像头 -- 配合定时器事件抓取图片

signals:
    void currentPictrueChanged(QImage);//采集的图片 --- 实时采集 -- 图片发送信号

private:
    QMediaCaptureSession *session;//抓图管理器
    QImageCapture *imgeCapture;//抓图器
    QMediaRecorder *recorder;//录像
    QCamera *camera; //摄像头类
    bool cameraState = false;//摄像头状态 false = 未开启 ，true = 开启
    QTimer *timer; //定时器 -- 定时抓拍
    int frameRate = 50;//摄像头帧率



};

#endif // QMYCAMERA_H
