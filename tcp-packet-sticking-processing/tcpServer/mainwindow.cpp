#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Server");
    connect(ui->btn_start, &QPushButton::clicked, this, &MainWindow::Listening_port);
    connect(ui->btn_select, &QPushButton::clicked, this, &MainWindow::selectFile);
    connect(ui->btn_Send, &QPushButton::clicked, this, &MainWindow::sendFile);

    ui->lineEdit_port->setText("8989");
    m_Server = new MyTcpServer(this);
    connect(m_Server, &MyTcpServer::newClient, this, [ = ](qintptr socket)
    {
        //处理子线程相关的动作
        QThread *subThread = new QThread;
        MyWork* worker = new MyWork(socket);
        worker->moveToThread(subThread);
        connect(this, &MainWindow::start, worker, &MyWork::working);

        connect(worker, &MyWork::done, this, [ = ]()
        {
            //不要试图让子线程去修改ui界面里的数据，Qt不允许子线程操作ui对象，只能交给主线程处理
            qDebug() << "销毁子线程和任务对象资源";
            subThread->quit();//调用quit方法过后，有些任务还没有做完
            subThread->wait();//调用wait方法过后，等待任务完成之后再终止子线程
            subThread->deleteLater();
            worker->deleteLater();
        });

        connect(worker, &MyWork::text, this, [ = ](QByteArray array)
        {
            QVector<QColor> colors =
            {
                Qt::red, Qt::green, Qt::black, Qt::blue, Qt::darkRed, Qt::cyan, Qt::magenta
            };
            int idx = QRandomGenerator::global()->bounded(colors.size());
            ui->messAge->setTextColor(colors.at(idx));
            ui->messAge->append(QString("%1").arg(array));
        });
        subThread->start();//启动子线程，子线程启动起来过后，内部的对象不一定在工作
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

//监听端口
void MainWindow::Listening_port()
{
    auto port = ui->lineEdit_port->text().toUShort();
    m_Server->listen(QHostAddress::Any, port);
    if (m_Server->isListening())
    {
        QMessageBox::information(this, "listen", "isListening!");
    }
}

//选择文件
void MainWindow::selectFile()
{
    QString path = QFileDialog::getOpenFileName(this);
    if (!path.isEmpty())
    {
        ui->lineEdit_file->setText(path);
        return;
    }
    else
    {
        QMessageBox::warning(this, "file", "file is Empty!");
        return;
    }
}

//发送文件
void MainWindow::sendFile()
{
    if (this->ui->lineEdit_file->text().isEmpty())
    {
        QMessageBox::information(this, "sendfile", "file is Empty!");
        return;
    }

    emit start(this->ui->lineEdit_file->text());
}

