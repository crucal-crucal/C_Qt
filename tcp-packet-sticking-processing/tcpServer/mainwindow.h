#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QThread>

#include "MyTcpServer.h"
#include "MyWork.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 signals:
  void start(QString name);  // 通知子线程可以工作了

 private slots:
  void Listening_port();  // 监听端口
  void selectFile();      // 选择文件
  void sendFile();        // 发送文件

 private:
  Ui::MainWindow *ui;
  MyTcpServer *m_Server;
};
#endif  // MAINWINDOW_H
