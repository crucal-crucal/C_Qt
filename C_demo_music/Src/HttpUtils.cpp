#include "HttpUtils.h"

HttpUtils::HttpUtils(QObject* parent) : QObject{parent} {
    mannager = new QNetworkAccessManager(this);
    QObject::connect(mannager, &QNetworkAccessManager::finished, this, &HttpUtils::replyFinished, Qt::UniqueConnection);
}

void HttpUtils::replyFinished(QNetworkReply* reply) {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
    emit replySignal(reply->readAll());
}

void HttpUtils::connect(QString url) {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
    QNetworkRequest request;
    request.setUrl(QUrl(BASH_URL + url));
    mannager->get(request);
}
