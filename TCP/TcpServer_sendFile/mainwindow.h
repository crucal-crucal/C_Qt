
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessagebox>
#include "recvfile.h"
#include "mytcpserver.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_Setlisten_clicked();

private:
    Ui::MainWindow *ui;

private:
    MyTcpServer *m_tcp;
};

#endif // MAINWINDOW_H
