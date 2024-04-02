#ifndef HTTPUTILS_H
#define HTTPUTILS_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>

class HttpUtils : public QObject {
    Q_OBJECT
  public:
    explicit HttpUtils(QObject* parent = nullptr);

    // 这样声明，Qml 就可以调用这个方法
    Q_INVOKABLE void replyFinished(QNetworkReply* reply);
    Q_INVOKABLE void connect(QString url);

  signals:
    void replySignal(QString);

  private:
    QNetworkAccessManager* mannager;
    QString BASH_URL = "http://localhost:3000/";
};

#endif  // HTTPUTILS_H
