<<<<<<< HEAD
<<<<<<< HEAD

=======
>>>>>>> 47b8f66 (update)
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
<<<<<<< HEAD
=======
<<<<<<<< HEAD:Chinese_to_pingyin/mainwindow.h
#include <QPushButton>
========
>>>>>>> 47b8f66 (update)
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessagebox>
#include <QHostInfo>
#include <QThread>
#include "recvfile.h"
#include "mytcpserver.h"
#include "form.h"
<<<<<<< HEAD
=======
>>>>>>>> 47b8f66 (update):TCP-1/TcpServer_sendFile/mainwindow.h
>>>>>>> 47b8f66 (update)

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

<<<<<<< HEAD
class MainWindow : public QMainWindow

=======
/*
 * 中文转化为拼音或者转化为简写拼音
*/

class MainWindow : public QMainWindow
>>>>>>> 47b8f66 (update)
{
    Q_OBJECT

    QString getLocalIP();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

<<<<<<< HEAD
private slots:
    void on_btn_Setlisten_clicked();

private:
    Ui::MainWindow *ui;
=======
    void zhToPY(); // 中文转为拼音
    void zhToJP(); // 中文转为简写拼音

private:
    Ui::MainWindow *ui;
<<<<<<<< HEAD:Chinese_to_pingyin/mainwindow.h
========
>>>>>>> 47b8f66 (update)

private:
    QTcpServer *m_tcp;
    QThread *m_t;
<<<<<<< HEAD
};

#endif // MAINWINDOW_H
=======

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessagebox>
#include <QHostInfo>
#include <QThread>
#include "recvfile.h"
#include "mytcpserver.h"
#include "form.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

    QString getLocalIP();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_Setlisten_clicked();

private:
    Ui::MainWindow *ui;

private:
    QTcpServer *m_tcp;
    QThread *m_t;
};

#endif // MAINWINDOW_H
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
=======
>>>>>>>> 47b8f66 (update):TCP-1/TcpServer_sendFile/mainwindow.h
};
#endif // MAINWINDOW_H
>>>>>>> 47b8f66 (update)
