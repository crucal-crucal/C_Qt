<<<<<<< HEAD

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
