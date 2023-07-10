
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myClients = new QMyClients;//do not give myClients a parent
    clientsThread = new QThread;//create a new Thread
    myClients->connectToServer();//connect the server
    /*@brief
     *  myClients->connectToServer();//connect the server
     * 在连接服务器的操作中，直接在主线程连接，避免在windows上出现句柄错误
     * 在主线程中连接服务器后将myClients对象通过moveThread移动到子线程 clientsThread 中即可避免windows句柄错误
     * 且myClients对象不可指定父对象，否则移动无效，且注意释放内存
     * */
    clientsThread->start();//start thread
    myClients->moveToThread(clientsThread);//move the Client to new thread

    sendVedioState = false;//默认不开启传输
    this->cameraThread = new QMyCameraThread;//创建摄像头线程
    qDebug() << "主线程:" << QThread::currentThread() << " - " << QThread::currentThreadId();

    connect(ui->endBtn, &QPushButton::clicked, this, &MainWindow::stopCamera); //关闭摄像头
    connect(ui->btn_Audio, &QPushButton::clicked, this, &MainWindow::sendAudio);//将声音数据上传到clientsThread线程(发送信号)
    connect(ui->startBtn, &QPushButton::clicked, this, &MainWindow::startCamera); //开启摄像头
    connect(ui->btn_sendMessage, &QPushButton::clicked, this, &MainWindow::sendMessage);//发送消息按钮
    connect(ui->stopShareBtn, &QPushButton::clicked, this, &MainWindow::stopShareDesktop); //关闭桌面共享
    connect(ui->send_picBtn, &QPushButton::clicked, this, &MainWindow::setSendServerState); //是否开启视频传输
    connect(ui->shareDesk_btn, &QPushButton::clicked, this, &MainWindow::startShareDesktop); //开启桌面共享
    /***************************************将信息显示到UI界面的槽******************************************************************************/
    connect(cameraThread, &QMyCameraThread::forwardCameraPic, this, &MainWindow::loadCameraPictrue); //将图片导入显示界面
    connect(cameraThread, &QMyCameraThread::forward_shareDesktopPic, this, &MainWindow::showSharePicToLabel); //显示桌面信息到界面


    /*****************************************************************************************************************************************/
    connect(this, &MainWindow::sendVedioToServer, myClients, &QMyClients::sendVideoToServer);//将视频数据上传到服务器
    connect(this, &MainWindow::sendMessageToServer, myClients, &QMyClients::sendMessageToSever); //文字消息
    connect(this, &MainWindow::sendAudioToServer, myClients, &QMyClients::sendAudiotoServer); //声音
    connect(this,&MainWindow::sendUserMessgeToServer,myClients,&QMyClients::sendUserMessgeToServer);//用户数据
    connect(cameraThread,&QMyCameraThread::forward_sendServerDeskPic,myClients,&QMyClients::sendDeskTopToServer);//将桌面数据发送给服务器

    /*****************************************************************************************************************************************/
    startCameraThread();//开启子线程，等待用户开启摄像头和桌面共享

}
MainWindow::~MainWindow()
{
    delete ui;

    clientsThread->terminate();

    terminateCameraThread();//强制中断线程
    delete myClients;
    delete clientsThread;
}
void MainWindow::loadCameraPictrue(QImage img)
{
    if (img.isNull()) return;
    QPixmap map = QPixmap::fromImage(img);
    ui->label->setPixmap(map.scaled(ui->label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)); //将摄像头数据显示到界面
    if (sendVedioState)
    {
        emit sendVedioToServer(map);
    }
}
/*****************************************************注*****************************************************************************/
/*@brief
 * 问题：由于开启摄像头和桌面共享均在子线程进行，而要让摄像头和桌面共享正常捕捉画面需要开启其内部的定时器，而主线程不能直接开启处在子线程里的定时器
 * 解决方法： 通过信号转发，先在主线程发送开启定时器信号到子线程，子线程接收到信号后再发送一次开启定时器信号给子线程里的摄像机对象和桌面对象，
            此时摄像机对象和桌面对象就可以开启或关闭定时器，来进行画面的捕捉和暂停
 * */
void MainWindow::startCamera()
{
    emit cameraThread->startCamera();//信号转发，cameraThread内部在进行一次开启信号发送
}
void MainWindow::startShareDesktop()
{
    emit cameraThread->startShareDesktop();//信号转发，cameraThread内部在进行一次开启信号发送
}
void MainWindow::stopCamera()
{
    emit cameraThread->stopCamera();//信号转发，cameraThread内部在进行一次关闭信号发送
}
void MainWindow::stopShareDesktop()
{
    emit cameraThread->stopShareDesktop();//信号转发，cameraThread内部在进行一次关闭信号发送
}
/**************************************************************************************************************************************/
void MainWindow::showSharePicToLabel(QPixmap map)
{
    //显示桌面画面到界面
    ui->label_shareDesktop->setPixmap(map.scaled(ui->label_shareDesktop->size(), Qt::KeepAspectRatio,Qt::SmoothTransformation));
}
void MainWindow::setSendServerState()
{
    if (this->sendVedioState) this->sendVedioState = false; //关闭传送视频数据到服务器
    else sendVedioState = true;//开启传送视频数据到服务器
}

void MainWindow::sendAudio()
{
    emit sendAudioToServer();
}
void MainWindow::startCameraThread()
{
    if (!this->cameraThread->isRunning()) //摄像头线程未启动就开启
        this->cameraThread->start();
}
void MainWindow::terminateCameraThread()
{
    if (this->cameraThread->isRunning()) //摄像头线程在工作，强行中断
        this->cameraThread->terminate();//强制中断子线程
}


void MainWindow::sendMessage()
{
    QString messAge = ui->lineEdit->text();
    ui->lineEdit->clear();
    QVector<QColor> colors =
    {
        Qt::red, Qt::green, Qt::black, Qt::blue, Qt::darkRed, Qt::cyan, Qt::magenta
    };
    int idx = QRandomGenerator::global()->bounded(colors.size());
    ui->textEdit->setTextColor(colors.at(idx));
    ui->textEdit->append(QString("send: %1").arg(messAge));
//    myClients->sendMessage(messAge);
    emit sendMessageToServer(messAge);
}

////键盘事件，方便发送消息
//void MainWindow::keyPressEvent(QKeyEvent *event)
//{
//    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
//    {
//        event->accept();
//        qDebug() << event->key();
//        this->sendMessage();
//    }
//}

