#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QMessageBox>
#include <QRandomGenerator>

#include "MyWork.h"

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
    void connectToServer();//连接到服务器

signals:
    void startToServer(QString ip, unsigned short port);//告诉子线程，可以连接到服务器了

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
