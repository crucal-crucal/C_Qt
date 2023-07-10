
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QLabel>
#include <QHostAddress>
#include <QHostInfo>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private:
    QTcpSocket  *tcpClient;   //socket
    QLabel  *labSocketState;  //状态栏显示标签

    QFile *localFile;  //要发送的文件
    qint64 totalBytes;  //数据总大小
    qint64 bytesWritten;  //已经发送数据大小
    qint64 bytesToWrite;   //剩余数据大小
    qint64 loadSize;   //每次发送数据的大小
    QString fileName;  //保存文件路径
    QByteArray outBlock;  //数据缓冲区，即存放每次要发送的数据
    QString  getLocalIP();    //获取本机IP地址

private slots:
    //自定义槽函数
    void    do_connected();
    void    do_disconnected();
    void    do_socketStateChange(QAbstractSocket::SocketState socketState);
    void    do_socketReadyRead();//读取socket传入的数据
    //
    void on_actConnect_triggered();

    void on_actDisconnect_triggered();

    void on_actClear_triggered();

    void on_btnSend_clicked();
    void on_act_openfile_triggered();
    void on_act_sendfile_triggered();
};

#endif // MAINWINDOW_H
