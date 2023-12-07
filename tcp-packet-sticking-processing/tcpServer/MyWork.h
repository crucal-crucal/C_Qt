#ifndef MYWORK_H
#define MYWORK_H

#include <QFile>
#include <QMessageBox>
#include <QObject>
#include <QTcpSocket>
#include <QThread>
#include <QtEndian>

class MyWork : public QObject {
  Q_OBJECT
 public:
  explicit MyWork(qintptr socket, QObject* parent = nullptr);

  void working(QString path);
 signals:
  void done();
  void text(QByteArray msg);

 private:
  qintptr m_socket;
  QTcpSocket* m_tcp;
};

#endif  // MYWORK_H
