
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

private slots:
    void dealSendSigFileInfo(QString name,qint64 received_size);
    void dealSendSigOver(QString,bool);

private:
    Form* getSendForm(QString);
    SendFile* getClientThread(QString);

signals:
    void startConnect(unsigned short , QString );

    void sendFile(QString);
private slots:
//    void on_btn_connectServer_clicked();

//    void on_btn_selFile_clicked();

    void on_btn_sendFile_clicked();

    void on_btn_selFile_clicked();

    void on_btn_connectServer_clicked();

    void on_act_disconnect_triggered();

private:
    Ui::MainWindow *ui;
    QMap<QString,Form*> m_mapSend;
    QMap<QString,SendFile*> m_mapClient;
    SendFile* worker;
    QThread* m_t;
};

#endif // MAINWINDOW_H
