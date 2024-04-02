<<<<<<< HEAD
<<<<<<< HEAD

#ifndef QMYTHREAD_H
#define QMYTHREAD_H

#include <QMessageBox>
#include <QObject>
#include <QRunnable>
#include <QTcpSocket>
#include <QThread>

/*@brief
 * 此线程专门为服务器提供，重写run方法并开启事件循环处理监听客户端请求
 *
 */
class QMyThread : public QObject {
  Q_OBJECT
public:
  explicit QMyThread(qintptr socket, QObject *parent = nullptr);
  ~QMyThread();

  void working();  // 工作函数
  void dealread(); // 处理信息函数

public slots:

private slots:
  //    void dealDisconnected();

signals:
  void recvVideo(QByteArray); // 传输数据
private:
  qintptr m_socket;
  QTcpSocket *mytcpSocket; // 在线程里创建套接字

  //    // QRunnable interface
  // public:
  //    void run();
};

#endif // QMYTHREAD_H
=======
=======
>>>>>>> 47b8f66 (update)

#ifndef QMYTHREAD_H
#define QMYTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QMessageBox>

#include "QMyDataDecompression.h"
/*@brief
 * 此线程专门为服务器提供，重写run方法并开启事件循环处理监听客户端请求
 *
*/
class QMyThread : public QObject
{
    Q_OBJECT
public:
    explicit QMyThread(qintptr socket, QObject *parent = nullptr);
    ~QMyThread();

    void working();//工作函数
    void dealread();//处理信息函数

public slots:

private slots:
//    void dealDisconnected();

signals:
    void recvVideo(QByteArray);//传输数据
private:
    qintptr m_socket;
    QTcpSocket* mytcpSocket; //在线程里创建套接字
};

#endif // QMYTHREAD_H
<<<<<<< HEAD
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
=======
>>>>>>> 47b8f66 (update)
