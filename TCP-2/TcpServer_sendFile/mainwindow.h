<<<<<<< HEAD

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include <QHostInfo>
#include <QThread>
#include <QTimer>
#include <QMap>
#include <QNetworkInterface>
#include "recvfile.h"
#include "form.h"

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
    void dealRecSigFileInfo(QString name, qint64 size, qint64 received_size);
    void dealRecSigOver(QTcpSocket*, QString, bool);

private slots:
    void on_btn_Setlisten_clicked();

private:
    void serverInit();

    bool getReceiveFirst(QString);
    Form* getReceiveForm(QString);
    RecvFile* getServerThread(QTcpSocket*);
private:
    Ui::MainWindow *ui;

private:
    QTcpServer* m_qtcpServer;
    RecvFile* serverThread;
    QMap<QString,Form*> m_mapReceive;
    QMap<QTcpSocket*,RecvFile*> m_mapTcpServer;
    bool m_recFlag;
    QList<QString> m_ListRecFirst;
};

#endif // MAINWINDOW_H
=======

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include <QHostInfo>
#include <QThread>
#include <QTimer>
#include <QMap>
#include <QNetworkInterface>
#include "recvfile.h"
#include "form.h"

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
    void dealRecSigFileInfo(QString name, qint64 size, qint64 received_size);
    void dealRecSigOver(QTcpSocket*, QString, bool);

private slots:
    void on_btn_Setlisten_clicked();

private:
    void serverInit();

    bool getReceiveFirst(QString);
    Form* getReceiveForm(QString);
    RecvFile* getServerThread(QTcpSocket*);
private:
    Ui::MainWindow *ui;

private:
    QTcpServer* m_qtcpServer;
    RecvFile* serverThread;
    QMap<QString,Form*> m_mapReceive;
    QMap<QTcpSocket*,RecvFile*> m_mapTcpServer;
    bool m_recFlag;
    QList<QString> m_ListRecFirst;
};

#endif // MAINWINDOW_H
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
