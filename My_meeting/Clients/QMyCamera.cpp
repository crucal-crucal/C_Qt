<<<<<<< HEAD
<<<<<<< HEAD

#include "QMyCamera.h"

QMyCamera::QMyCamera(QObject *parent) : QObject{parent} {
  QCameraDevice defualtCamera = QMediaDevices::defaultVideoInput();
  if (defualtCamera.isNull()) {
    QMessageBox::critical(nullptr, "提示", "亲，没有发现摄像头");
  }
  this->timer = new QTimer(this);
  this->camera = new QCamera(this);
  this->imgeCapture = new QImageCapture(this);    // 抓图器
  this->session = new QMediaCaptureSession(this); // 抓图管理器
  this->camera->setCameraDevice(
      QMediaDevices::defaultVideoInput()); // 为相机设置默认设备

  this->imgeCapture->setQuality(
      QImageCapture::VeryHighQuality);               // 设置为高质量图片
  this->session->setCamera(this->camera);            // 设置相机
  this->session->setImageCapture(this->imgeCapture); // 抓图片
  connect(this->imgeCapture, &QImageCapture::imageCaptured, this,
          &QMyCamera::getImage); // 将抓取的图片发送出去
  connect(timer, &QTimer::timeout, this,
          &QMyCamera::catchCamera); // 定时抓取摄像头
}

QMyCamera::~QMyCamera() {
  if (this->timer->isActive()) {
    this->timer->stop();
  }
}

void QMyCamera::setCameraRate(int ms) {
  frameRate = ms;
  if (!this->timer->isActive())
    this->timer->start(frameRate);
  else {
    this->timer->stop();
    this->timer->start(frameRate);
  }
}

void QMyCamera::startCamera() {
  this->camera->start();
  if (this->camera->isActive()) {
    qDebug() << "摄像头开启成功！";
  }
  if (!this->timer->isActive())
    this->timer->start(frameRate);
}

void QMyCamera::stopCamera() {
  this->camera->stop();
  if (this->timer->isActive()) {
    this->timer->stop();
  }
  if (!this->camera->isActive()) {
    qDebug() << "摄像头关闭！";
  }
}

void QMyCamera::getImage(int id, const QImage &preview) {
  Q_UNUSED(id);

  if (preview.isNull()) {
    qDebug() << "image null!";
    return;
  }
  QImage scaledImage = preview.scaledToWidth(400);
  // scaledImage = scaledImage.scaled(400, 400, Qt::KeepAspectRatio,
  // Qt::FastTransformation);
  emit currentPictrueChanged(scaledImage); // 发送出去
}

void QMyCamera::catchCamera() {
  this->imgeCapture->capture(); // 开始摄像头捕获一张图片
}
/*
   scaledImage = scaledImage.convertToFormat(QImage::Format_ARGB32);
    // 对肤色进行高斯滤波处理
    QImage smoothImage = preview;
   smoothImage = smoothImage.scaled(300, 300,Qt::KeepAspectRatio);
    smoothImage = smoothImage.convertToFormat(QImage::Format_RGB32);
     int radius = 1;
    QImage smoothImage2 = smoothImage.copy();
    QRgb* pixel = reinterpret_cast<QRgb*>(smoothImage.bits());
    QRgb* pixel2 = reinterpret_cast<QRgb*>(smoothImage2.bits());
    for (int y = 0; y < smoothImage.height(); y++) {
        for (int x = 0; x < smoothImage.width(); x++) {
            int r = 0, g = 0, b = 0, count = 0;
            for (int dy = -radius; dy <= radius; dy++) {
                for (int dx = -radius; dx <= radius; dx++) {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx >= 0 && nx < smoothImage.width() && ny >= 0 && ny <
 smoothImage.height()) { QRgb color = pixel[nx + ny * smoothImage.width()]; r +=
 qRed(color); g += qGreen(color); b += qBlue(color); count++;
                    }
                }
            }
            pixel2[x + y * smoothImage.width()] = qRgb(r / count, g / count, b /
 count);
        }
    }
 *
 * */
=======
=======
>>>>>>> 47b8f66 (update)

#include "QMyCamera.h"

QMyCamera::QMyCamera(QObject *parent): QObject{parent}
{
    QCameraDevice defualtCamera = QMediaDevices::defaultVideoInput();
    if (defualtCamera.isNull())
    {
        QMessageBox::critical(nullptr, "提示", "亲，没有发现摄像头");
    }
    this->timer = new QTimer(this);
    this->camera = new QCamera(this);
    this->imgeCapture = new QImageCapture(this);//抓图器
    this->session = new QMediaCaptureSession(this);//抓图管理器
    this->camera->setCameraDevice(QMediaDevices::defaultVideoInput());//为相机设置默认设备

    this->imgeCapture->setQuality(QImageCapture::VeryHighQuality);//设置为高质量图片
    this->session->setCamera(this->camera);//设置相机
    this->session->setImageCapture(this->imgeCapture);//抓图片
    connect(this->imgeCapture, &QImageCapture::imageCaptured, this, &QMyCamera::getImage); //将抓取的图片发送出去
    connect(timer, &QTimer::timeout, this, &QMyCamera::catchCamera); //定时抓取摄像头
}
QMyCamera::~QMyCamera()
{
    if (this->timer->isActive())
    {
        this->timer->stop();
    }
}
void QMyCamera::setCameraRate(int ms)
{
    frameRate = ms;
    if (!this->timer->isActive())
        this->timer->start(frameRate);
    else
    {
        this->timer->stop();
        this->timer->start(frameRate);
    }
}
void QMyCamera::startCamera()
{
    this->camera->start();
    if (this->camera->isActive())
    {
        qDebug() << "摄像头开启成功！";
    }
    if (!this->timer->isActive())
        this->timer->start(frameRate);
}
void QMyCamera::stopCamera()
{
    this->camera->stop();
    if (this->timer->isActive())
    {
        this->timer->stop();
    }
    if (!this->camera->isActive())
    {
        qDebug() << "摄像头关闭！";
    }
}
void QMyCamera::getImage(int id, const QImage &preview)
{
    if (preview.isNull())
    {
        qDebug() << "image null!";
        return;
    }
    QImage scaledImage = preview.scaledToWidth(400);
    //scaledImage = scaledImage.scaled(400, 400, Qt::KeepAspectRatio, Qt::FastTransformation);
    emit currentPictrueChanged(scaledImage);//发送出去
}
void QMyCamera::catchCamera()
{
    this->imgeCapture->capture();//开始摄像头捕获一张图片
}
/*
   scaledImage = scaledImage.convertToFormat(QImage::Format_ARGB32);
    // 对肤色进行高斯滤波处理
    QImage smoothImage = preview;
   smoothImage = smoothImage.scaled(300, 300,Qt::KeepAspectRatio);
    smoothImage = smoothImage.convertToFormat(QImage::Format_RGB32);
     int radius = 1;
    QImage smoothImage2 = smoothImage.copy();
    QRgb* pixel = reinterpret_cast<QRgb*>(smoothImage.bits());
    QRgb* pixel2 = reinterpret_cast<QRgb*>(smoothImage2.bits());
    for (int y = 0; y < smoothImage.height(); y++) {
        for (int x = 0; x < smoothImage.width(); x++) {
            int r = 0, g = 0, b = 0, count = 0;
            for (int dy = -radius; dy <= radius; dy++) {
                for (int dx = -radius; dx <= radius; dx++) {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx >= 0 && nx < smoothImage.width() && ny >= 0 && ny < smoothImage.height()) {
                        QRgb color = pixel[nx + ny * smoothImage.width()];
                        r += qRed(color);
                        g += qGreen(color);
                        b += qBlue(color);
                        count++;
                    }
                }
            }
            pixel2[x + y * smoothImage.width()] = qRgb(r / count, g / count, b / count);
        }
    }
 *
 * */
<<<<<<< HEAD
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
=======
>>>>>>> 47b8f66 (update)
