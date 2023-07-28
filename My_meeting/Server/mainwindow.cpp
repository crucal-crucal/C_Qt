
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->lineEdit_port->setText("8989");                   // 设置端口为8989
  myServer = new QMyServer(this);                       // 主线程服务器
  myDataDecompression = new QMyDataDecompression(this); // 自定义协议
  myServer->serverInit();                               // 初始化服务器
  QAudioFormat daqFormat;
  daqFormat.setSampleRate(44100);                 // 采样频率
  daqFormat.setChannelCount(1);                   // 通道个数
  daqFormat.setSampleFormat(QAudioFormat::UInt8); // 采样点格式
  audioSink = new QAudioSink(daqFormat, this);
  connect(ui->btn_Monitor, &QPushButton::clicked, this,
          &MainWindow::Listening_port); // 监听端口按钮
  connect(myServer, &QMyServer::recvVideo, this, [&](QByteArray array) {
#ifdef NDEBUG
    static qsizetype size{};
    static int cnt{};
    qDebug() << "array-size:    " << array.size() << "cnt:  " << cnt;
    size += array.size(), cnt++;
    qDebug() << "size:    " << size;
#endif
    //        this->showAudiotoUI(array);
    myDataDecompression->startExtractPacked(
        array); // 处理来自客户端的数据包，目前会发出三个信号，连接到处理函数即可
    qDebug() << "size::\t" << array.size();
  });
  connect(myDataDecompression,
          &QMyDataDecompression::finished_extractPictrueData, this,
          &MainWindow::showPicture); // 摄像头
  connect(myDataDecompression, &QMyDataDecompression::finished_extractTextData,
          this, &MainWindow::showText); // 文本
  connect(myDataDecompression, &QMyDataDecompression::finished_extractVideoData,
          this, &MainWindow::showVideo); // 音视频
}

MainWindow::~MainWindow() { delete ui; }

// 在UI上显示图像
void MainWindow::showPicturetoUI(QByteArray array) {
  QImage img = QImage::fromData(array); // 将接收到的字节数组转化为QImage
  //    QPixmap map = myDataDecompression->changedByteArrayToPixmap(array);
  ui->lab_Video->setPixmap(QPixmap::fromImage(img)); // 再将其设置在label上
}

// 在UI上开启音频
void MainWindow::showAudiotoUI(QByteArray array) {
  QIODevice *audioSink1 = audioSink->start(); // 使用audioSink组件捕获音频数组
  audioSink1->write(array.constData(),
                    array.size()); // 将文件写入audioSink，用于播放音频
}
// 监听端口
void MainWindow::Listening_port() {
  unsigned short port = ui->lineEdit_port->text().toUShort(); // 端口
  myServer->serverListen(port);                               // 监听端口
}
// 显示图像
void MainWindow::showPicture(QByteArray array) { this->showPicturetoUI(array); }
// 显示文本
void MainWindow::showText(QString text) {
  // 随机颜色，方便测试每次发送是否成功
  QVector<QColor> colors = {Qt::red,     Qt::green, Qt::black,  Qt::blue,
                            Qt::darkRed, Qt::cyan,  Qt::magenta};
  int idx = QRandomGenerator::global()->bounded(colors.size());
  ui->messAge->setTextColor(colors.at(idx));
  ui->messAge->append(QString("Client: %1").arg(text));
}
// 开启音视频
void MainWindow::showVideo(QByteArray video, QByteArray audio) {
#ifdef NDEBUG
  qDebug() << "video.size():\t" << video.size();
  qDebug() << "audio.size():\t" << audio.size();
#endif
  this->showPicturetoUI(video);
  this->showAudiotoUI(audio);
}
