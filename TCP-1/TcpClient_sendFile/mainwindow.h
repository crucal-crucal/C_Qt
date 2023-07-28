<<<<<<< HEAD

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QMessageBox>
#include <QFileDialog>
#include <QHostInfo>
#include "sendfile.h"
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

    void moveThread();

signals:
    void startConnect(unsigned short, QString);

    void sendFile(QString);

private slots:
    void on_btn_connectServer_clicked();

    void on_btn_selFile_clicked();

    void on_btn_sendFile_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
=======

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QMessageBox>
#include <QFileDialog>
#include <QHostInfo>
#include "sendfile.h"
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

    void moveThread();

signals:
    void startConnect(unsigned short, QString);

    void sendFile(QString);

private slots:
    void on_btn_connectServer_clicked();

    void on_btn_selFile_clicked();

    void on_btn_sendFile_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
