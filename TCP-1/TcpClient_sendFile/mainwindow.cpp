<<<<<<< HEAD

#include "mainwindow.h"
#include "ui_mainwindow.h"


QString MainWindow::getLocalIP()
{
    //获取本机IPv4地址
    QString hostName = QHostInfo::localHostName();    //本地主机名
    QHostInfo hostInfo = QHostInfo::fromName(hostName);
    QString   localIP = "";

    QList<QHostAddress> addList=hostInfo.addresses();  //本机IP地址列表
    if (addList.isEmpty())
        return localIP;

    foreach(QHostAddress aHost, addList)
        if (QAbstractSocket::IPv4Protocol==aHost.protocol())
        {
            localIP=aHost.toString();
            break;
        }
    return localIP;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->IP->setText(getLocalIP());
    ui->Port->setText("8989");
    ui->progressBar->setRange(0, 100);
    ui->progressBar->setValue(0);

    moveThread();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::moveThread()
{
    //创建线程对象
    QThread *m_t = new QThread;
    //创建任务对象（不能创建父对象
    SendFile *worker = new SendFile;

    worker->moveToThread(m_t);

    //主线程发送信号给子线程，表示发送文件
    connect(this, &MainWindow::sendFile, worker, &SendFile::sendFile);

    //主窗口向线程发送连接成功的信号
    connect(this, &MainWindow::startConnect, worker, &SendFile::connectServer);

    //处理子线程发送过来的信号
    connect(worker, &SendFile::connectSuc, this, [=](){
        QMessageBox::information(this, "连接服务器", "连接服务器成功");
        ui->statusbar->addWidget(new QLabel("已连接"));
    });

    //断开连接处理资源释放
    connect(worker, &SendFile::disConnect, this, [=](){
        ui->statusbar->addWidget(new QLabel("已断开"));
        m_t->quit();
        m_t->wait();
        worker->deleteLater();
        m_t->deleteLater();
    });

    //接受子线程发送的信号，更新进度条
    connect(worker, &SendFile::curPercent, ui->progressBar, &QProgressBar::setValue);

    m_t->start();//开启线程
}


//连接服务器
void MainWindow::on_btn_connectServer_clicked()
{
    QString ip = ui->IP->text();
    unsigned short port = ui->Port->text().toUShort();
    emit startConnect(port, ip);
}

//打开文件
void MainWindow::on_btn_selFile_clicked()
{
    QString filepath = QFileDialog::getOpenFileName();
    if(!filepath.isEmpty())
        ui->filePath->setText(filepath);
    else
    {
        QMessageBox::warning(this, "打开文件", "选择的文件路径不能为空！！");
        return;
    }
}

//发送文件
void MainWindow::on_btn_sendFile_clicked()
{
    QString filepath = ui->filePath->text();
    emit sendFile(filepath);
}

=======

#include "mainwindow.h"
#include "ui_mainwindow.h"


QString MainWindow::getLocalIP()
{
    //获取本机IPv4地址
    QString hostName = QHostInfo::localHostName();    //本地主机名
    QHostInfo hostInfo = QHostInfo::fromName(hostName);
    QString   localIP = "";

    QList<QHostAddress> addList=hostInfo.addresses();  //本机IP地址列表
    if (addList.isEmpty())
        return localIP;

    foreach(QHostAddress aHost, addList)
        if (QAbstractSocket::IPv4Protocol==aHost.protocol())
        {
            localIP=aHost.toString();
            break;
        }
    return localIP;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->IP->setText(getLocalIP());
    ui->Port->setText("8989");
    ui->progressBar->setRange(0, 100);
    ui->progressBar->setValue(0);

    moveThread();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::moveThread()
{
    //创建线程对象
    QThread *m_t = new QThread;
    //创建任务对象（不能创建父对象
    SendFile *worker = new SendFile;

    worker->moveToThread(m_t);

    //主线程发送信号给子线程，表示发送文件
    connect(this, &MainWindow::sendFile, worker, &SendFile::sendFile);

    //主窗口向线程发送连接成功的信号
    connect(this, &MainWindow::startConnect, worker, &SendFile::connectServer);

    //处理子线程发送过来的信号
    connect(worker, &SendFile::connectSuc, this, [=](){
        QMessageBox::information(this, "连接服务器", "连接服务器成功");
        ui->statusbar->addWidget(new QLabel("已连接"));
    });

    //断开连接处理资源释放
    connect(worker, &SendFile::disConnect, this, [=](){
        ui->statusbar->addWidget(new QLabel("已断开"));
        m_t->quit();
        m_t->wait();
        worker->deleteLater();
        m_t->deleteLater();
    });

    //接受子线程发送的信号，更新进度条
    connect(worker, &SendFile::curPercent, ui->progressBar, &QProgressBar::setValue);

    m_t->start();//开启线程
}


//连接服务器
void MainWindow::on_btn_connectServer_clicked()
{
    QString ip = ui->IP->text();
    unsigned short port = ui->Port->text().toUShort();
    emit startConnect(port, ip);
}

//打开文件
void MainWindow::on_btn_selFile_clicked()
{
    QString filepath = QFileDialog::getOpenFileName();
    if(!filepath.isEmpty())
        ui->filePath->setText(filepath);
    else
    {
        QMessageBox::warning(this, "打开文件", "选择的文件路径不能为空！！");
        return;
    }
}

//发送文件
void MainWindow::on_btn_sendFile_clicked()
{
    QString filepath = ui->filePath->text();
    emit sendFile(filepath);
}

>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
