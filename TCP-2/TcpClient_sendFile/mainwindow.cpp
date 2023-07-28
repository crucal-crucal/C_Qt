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

    setWindowTitle("Clients");
    resize(400, 300);
    ui->IP->setText("127.0.0.1");
    ui->Port->setText("8989");
    ui->btn_sendFile->setEnabled(false);

    m_t = new QThread;

    worker = new SendFile;

    worker->moveToThread(m_t);

    connect(this, &MainWindow::startConnect, worker, &SendFile::connectServer);
    connect(this, &MainWindow::sendFile, worker, &SendFile::sendFile);
    connect(worker, &SendFile::connectSuc, this, [=](){
        QMessageBox::information(this, "连接服务器", "连接服务器成功！！！");
        ui->statusbar->addWidget(new QLabel("已连接"));
    });
    connect(worker, &SendFile::sigFileInfo, this, &MainWindow::dealSendSigFileInfo);
    connect(worker, &SendFile::sigOver, this, &MainWindow::dealSendSigOver);
    m_t->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dealSendSigFileInfo(QString name, qint64 received_size)
{
    /*更新发送进度*/
    qApp->processEvents();
    getSendForm(name)->updateProcess(received_size);
}

void MainWindow::dealSendSigOver(QString fileTime, bool bl)
{
    qDebug()<<"dealSendSigOver:";
    QMessageBox::information(this, "发送文件", "发送文件完成！");
    getSendForm(fileTime)->setStatus(bl);
}

//传入Tcp， 返回传输界面
Form* MainWindow::getSendForm(QString fileNameTime)
{
    for (auto itor = m_mapSend.begin(); itor != m_mapSend.end(); itor++)
    {
        if(itor.key() == fileNameTime)
        {
            return itor.value();
        }
    }
    return nullptr;
}

//传入文件名，然会传输线程
SendFile* MainWindow::getClientThread(QString fileNameTime)
{
    for (auto itor = m_mapClient.begin(); itor != m_mapClient.end(); itor++)
    {
        if(itor.key() == fileNameTime)
        {
            return itor.value();
        }
    }
    return nullptr;
}

//发送文件
void MainWindow::on_btn_sendFile_clicked()
{
    QString filePath = ui->filePath->text();
    /*加上时间，区分ClientThread*/
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("MMddhhmmsszzz");

    qDebug()<<"current_date:"<<current_date;

    /*文件传输界面*/
    QFileInfo info(filePath);
    Form* form = new Form(info.fileName(),info.size());
    ui->verticalLayout_2->addWidget(form);
    qDebug()<<"filePath:"<<info.fileName()<<":"<<info.size();

    /*线程发送文件，这里传到线程的文件路径是已经加了当前时间字符串的，
     * 线程中会处理在获取正在的文件路径，
     * 加时间字符串是以免文件名相同，
     * 后面获取传输界面会有问题*/

//    SendFile* clientThread = new SendFile(port, ip, filePath+"##"+current_date);
//    connect(worker, &SendFile::sigFileInfo, this, &MainWindow::dealSendSigFileInfo);
//    connect(worker, &SendFile::sigOver, this, &MainWindow::dealSendSigOver);
//    clientThread->start();
    m_t->start();

    /*字典，<处理后的文件名，线程>，*/
    m_mapClient.insert(info.fileName()+"##"+current_date,worker);
    /*字典，<处理后的文件名，传输界面>，*/
    m_mapSend.insert(info.fileName()+"##"+current_date,form);

    emit sendFile(filePath + "##" + current_date);
}


void MainWindow::on_btn_selFile_clicked()
{
    QString path = QFileDialog::getOpenFileName();
    ui->filePath->setText(path);
    ui->btn_sendFile->setEnabled(true);
}


void MainWindow::on_btn_connectServer_clicked()
{
    unsigned short port = ui->Port->text().toUShort();
    QString ip = ui->IP->text();
    emit startConnect(port, ip);
}


void MainWindow::on_act_disconnect_triggered()
{
    /*关闭线程*/
//    worker = getClientThread(fileTime);
    QMessageBox::information(this, "服务器", "已断开连接！");
    ui->statusbar->addWidget(new QLabel("已断开"));
    m_t->quit();
    m_t->wait();
    worker->deleteLater();
    m_t->deleteLater();
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

    setWindowTitle("Clients");
    resize(400, 300);
    ui->IP->setText("127.0.0.1");
    ui->Port->setText("8989");
    ui->btn_sendFile->setEnabled(false);

    m_t = new QThread;

    worker = new SendFile;

    worker->moveToThread(m_t);

    connect(this, &MainWindow::startConnect, worker, &SendFile::connectServer);
    connect(this, &MainWindow::sendFile, worker, &SendFile::sendFile);
    connect(worker, &SendFile::connectSuc, this, [=](){
        QMessageBox::information(this, "连接服务器", "连接服务器成功！！！");
        ui->statusbar->addWidget(new QLabel("已连接"));
    });
    connect(worker, &SendFile::sigFileInfo, this, &MainWindow::dealSendSigFileInfo);
    connect(worker, &SendFile::sigOver, this, &MainWindow::dealSendSigOver);
    m_t->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dealSendSigFileInfo(QString name, qint64 received_size)
{
    /*更新发送进度*/
    qApp->processEvents();
    getSendForm(name)->updateProcess(received_size);
}

void MainWindow::dealSendSigOver(QString fileTime, bool bl)
{
    qDebug()<<"dealSendSigOver:";
    QMessageBox::information(this, "发送文件", "发送文件完成！");
    getSendForm(fileTime)->setStatus(bl);
}

//传入Tcp， 返回传输界面
Form* MainWindow::getSendForm(QString fileNameTime)
{
    for (auto itor = m_mapSend.begin(); itor != m_mapSend.end(); itor++)
    {
        if(itor.key() == fileNameTime)
        {
            return itor.value();
        }
    }
    return nullptr;
}

//传入文件名，然会传输线程
SendFile* MainWindow::getClientThread(QString fileNameTime)
{
    for (auto itor = m_mapClient.begin(); itor != m_mapClient.end(); itor++)
    {
        if(itor.key() == fileNameTime)
        {
            return itor.value();
        }
    }
    return nullptr;
}

//发送文件
void MainWindow::on_btn_sendFile_clicked()
{
    QString filePath = ui->filePath->text();
    /*加上时间，区分ClientThread*/
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("MMddhhmmsszzz");

    qDebug()<<"current_date:"<<current_date;

    /*文件传输界面*/
    QFileInfo info(filePath);
    Form* form = new Form(info.fileName(),info.size());
    ui->verticalLayout_2->addWidget(form);
    qDebug()<<"filePath:"<<info.fileName()<<":"<<info.size();

    /*线程发送文件，这里传到线程的文件路径是已经加了当前时间字符串的，
     * 线程中会处理在获取正在的文件路径，
     * 加时间字符串是以免文件名相同，
     * 后面获取传输界面会有问题*/

//    SendFile* clientThread = new SendFile(port, ip, filePath+"##"+current_date);
//    connect(worker, &SendFile::sigFileInfo, this, &MainWindow::dealSendSigFileInfo);
//    connect(worker, &SendFile::sigOver, this, &MainWindow::dealSendSigOver);
//    clientThread->start();
    m_t->start();

    /*字典，<处理后的文件名，线程>，*/
    m_mapClient.insert(info.fileName()+"##"+current_date,worker);
    /*字典，<处理后的文件名，传输界面>，*/
    m_mapSend.insert(info.fileName()+"##"+current_date,form);

    emit sendFile(filePath + "##" + current_date);
}


void MainWindow::on_btn_selFile_clicked()
{
    QString path = QFileDialog::getOpenFileName();
    ui->filePath->setText(path);
    ui->btn_sendFile->setEnabled(true);
}


void MainWindow::on_btn_connectServer_clicked()
{
    unsigned short port = ui->Port->text().toUShort();
    QString ip = ui->IP->text();
    emit startConnect(port, ip);
}


void MainWindow::on_act_disconnect_triggered()
{
    /*关闭线程*/
//    worker = getClientThread(fileTime);
    QMessageBox::information(this, "服务器", "已断开连接！");
    ui->statusbar->addWidget(new QLabel("已断开"));
    m_t->quit();
    m_t->wait();
    worker->deleteLater();
    m_t->deleteLater();
}

>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
