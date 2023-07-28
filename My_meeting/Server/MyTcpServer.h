#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>

class MyTcpServer : public QTcpServer {
  Q_OBJECT
public:
  explicit MyTcpServer(QObject *parent = nullptr);

signals:
  void newClient(qintptr sockt);

  // QTcpServer interface
protected:
  void incomingConnection(qintptr handle);
};

#endif // MYTCPSERVER_H
