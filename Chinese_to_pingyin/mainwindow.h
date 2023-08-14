#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
<<<<<<<< HEAD:Chinese_to_pingyin/mainwindow.h
#include <QPushButton>
========
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessagebox>
#include <QHostInfo>
#include <QThread>
#include "recvfile.h"
#include "mytcpserver.h"
#include "form.h"
>>>>>>>> 47b8f66 (update):TCP-1/TcpServer_sendFile/mainwindow.h

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*
 * 中文转化为拼音或者转化为简写拼音
*/

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QString getLocalIP();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void zhToPY(); // 中文转为拼音
    void zhToJP(); // 中文转为简写拼音

private:
    Ui::MainWindow *ui;
<<<<<<<< HEAD:Chinese_to_pingyin/mainwindow.h
========

private:
    QTcpServer *m_tcp;
    QThread *m_t;
>>>>>>>> 47b8f66 (update):TCP-1/TcpServer_sendFile/mainwindow.h
};
#endif // MAINWINDOW_H
