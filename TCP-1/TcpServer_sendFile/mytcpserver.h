
#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H


#include <QTcpServer>
#include <QList>

class MyTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);

signals:
    void newDescriptor(qintptr);

    // QTcpServer interface
protected:
    void incomingConnection(qintptr handle);

private:
    QList<QTcpSocket *> clientlist;
};

#endif // MYTCPSERVER_H
