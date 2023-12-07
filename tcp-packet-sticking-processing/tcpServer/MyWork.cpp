#include "MyWork.h"

MyWork::MyWork(qintptr socket, QObject *parent) : QObject{parent} {
  m_socket = socket;
}

void MyWork::working(QString path) {
  qDebug() << "now id : " << QThread::currentThread();
  m_tcp =
      new QTcpSocket;  // 不能在构造函数里实例化，因为构造函数里是主线程在操作
  m_tcp->setSocketDescriptor(m_socket);  // 设置好之后，就可以通信了

  // 断开连接
  connect(m_tcp, &QTcpSocket::disconnected, this, [=]() {
    m_tcp->close();
    m_tcp->deleteLater();
    emit done();
    qDebug() << "over!";
  });
  qDebug() << "file path:" << path;

  QFile file(path);
  bool bl = file.open(QFile::ReadOnly);
  if (!bl) {
    QMessageBox::warning(nullptr, "file", "file open error!");
    return;
  }

  while (!file.atEnd()) {
    QByteArray line = file.readLine();
    // 添加包头
    // 将数据转换为大段数据
    // 此函数内操作对象是什么类型，返回的就是什么类型
    // 大端存储转化为小端存储
    int len = qToLittleEndian(line.size());
    // 包头,reinterpret_cast转换类型操作符
    //        QByteArray data((char*)&len, 4);
    QByteArray data(reinterpret_cast<char *>(&len), 4);
    data.append(line);

    m_tcp->write(data);  // 发送数据
    emit text(line);
    // 休眠50ms
    // 以免出现丢包的情况
    QThread::msleep(50);
  }

  file.close();
}
