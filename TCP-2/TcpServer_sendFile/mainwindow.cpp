
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Server");
    resize(400, 200);
    ui->port->setText("8989");
    //打印线程地址
    qDebug()<<"服务器主线程："<<QThread::currentThread();
    serverInit();
}

void MainWindow::serverInit()
{
    m_qtcpServer = new QTcpServer(this);
    connect(m_qtcpServer, &QTcpServer::newConnection, this, [=](){
        /*客户端连接，要接收文件了*/
        QTcpSocket *tcpSocket = m_qtcpServer->nextPendingConnection();

        serverThread = new RecvFile(tcpSocket);
        connect(serverThread, &RecvFile::sigFileInfo, this, &MainWindow::dealRecSigFileInfo);
        connect(serverThread, &RecvFile::sigOver, this, &MainWindow::dealRecSigOver);
        serverThread->start();
        m_mapTcpServer.insert(tcpSocket,serverThread);
        qDebug()<<"dealNewConnection:";
    });
}

bool MainWindow::getReceiveFirst(QString name)
{
    if(m_ListRecFirst.length() == 0)
        return true;

    for (int i=0;i<m_ListRecFirst.length(); i++)
    {
        if(name == m_ListRecFirst.at(i))
        {
            return false;
        }
    }
    return true;
}


Form* MainWindow::getReceiveForm(QString fileNameTime)
{
    for (auto itor = m_mapReceive.begin(); itor != m_mapReceive.end(); itor++)
    {
        if(itor.key() == fileNameTime)
        {
            return itor.value();
        }
    }
    return nullptr;
}


RecvFile* MainWindow::getServerThread(QTcpSocket *tcp)
{
    for (auto itor = m_mapTcpServer.begin(); itor != m_mapTcpServer.end(); itor++)
    {
        if(itor.key() == tcp)
        {
            return itor.value();
        }
    }
    return nullptr;
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::dealRecSigFileInfo(QString name, qint64 size, qint64 received_size)
{
    /*更新接收进度*/
    //在当前线程中处理所有待处理事件，不会等待新的事件的到来
    qApp->processEvents();

    if(getReceiveFirst(name))
    {
        Form* form = new Form(name.section("##", 0, 0), size);
        ui->verticalLayout_Server->addWidget(form);
        m_ListRecFirst.append(name);
        m_mapReceive.insert(name, form);
    }
    getReceiveForm(name)->updateProcess(received_size);
}

void MainWindow::dealRecSigOver(QTcpSocket *tcp, QString name, bool bl)
{
    /*文件接收完毕，关闭线程*/
    serverThread = getServerThread(tcp);
    serverThread->deleteData();
    serverThread->exit();
    serverThread->wait();
    serverThread->deleteLater();

    getReceiveForm(name)->setStatus(bl);
    if(bl) QMessageBox::information(this, "接收文件", "接收文件完成！！");
    else QMessageBox::information(this, "接收文件", "接收文件终端或传输错误！！！");
    qDebug()<<"dealRecSigOver:";
}

void MainWindow::on_btn_Setlisten_clicked()
{
    unsigned short port = ui->port->text().toUShort();
    m_qtcpServer->listen(QHostAddress::Any, port);
    if(m_qtcpServer->isListening())
        QMessageBox::information(this, "监听端口", QString("监听%1端口成功!!").arg(port));
    //    qDebug()<<getLocalIP();
}
