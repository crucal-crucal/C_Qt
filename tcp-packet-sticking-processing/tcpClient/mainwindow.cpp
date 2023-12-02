#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Client");
    connect(ui->btn_Connect, &QPushButton::clicked, this, &MainWindow::connectToServer); //连接到服务器

    qDebug() << "主线程线程id：" << QThread::currentThread();

    ui->lineEdit_ip->setText("127.0.0.1");
    ui->lineEdit_port->setText("8989");
    //创建子线程
    QThread* subThread = new QThread;
    MyWork* worker = new MyWork;
    //worker工作有两个条件
    //1.启动子线程
    //2.信号告诉worker对象，可以在子线程里工作了
    worker->moveToThread(subThread);

    connect(this, &MainWindow::startToServer, worker, &MyWork::connectToServer);
    connect(worker, &MyWork::connectOK, this, [ = ]()
    {
        QMessageBox::information(this, "Server", "successful!");
    });
    connect(worker, &MyWork::messAge, this, [ = ](QByteArray msg)
    {
        //用于区分一次接收完还是分批次
        QVector<QColor> colors =
        {
            Qt::red, Qt::green, Qt::black, Qt::blue, Qt::darkRed, Qt::cyan, Qt::magenta
        };
        int idx = QRandomGenerator::global()->bounded(colors.size());//生成一个0~colors.size()左开右闭的随机数
        ui->textEdit->setTextColor(colors.at(idx));
        ui->textEdit->append(QString("%1").arg(msg));
    });

    //传输完成，关闭子线程
    connect(worker, &MyWork::gameOver, this, [ = ]()
    {
        qDebug() << "over";
        subThread->quit();
        subThread->wait();
        subThread->deleteLater();
        worker->deleteLater();
    });
    subThread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectToServer()
{
    QString ip = ui->lineEdit_ip->text();
    unsigned short port = ui->lineEdit_port->text().toUShort();
    emit startToServer(ip, port);
}

