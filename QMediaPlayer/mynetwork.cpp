
#include "mynetwork.h"

MyNetWork::MyNetWork(QObject *parent)
    : QObject{parent}
{
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply){
        QMetaObject::invokeMethod(this, "DataBack", Q_ARG(QNetworkReply *, reply));
    });
}

void MyNetWork::search(QString keywords)
{
    QNetworkRequest request;
    request.setUrl(QUrl(front + keywords + back));
    manager->get(request);
    qDebug()<<"请求已发出";
}

void MyNetWork::DataBack(QNetworkReply *reply)
{
    qDebug()<<"=============================================网易API搜索=====================================";
    qDebug()<<"线程:"<<QThread::currentThread()<<" id:"<<QThread::currentThreadId();
        qDebug()<<"////////////////////////////////////////////////////////////////////////////////////////////";
    QByteArray searchInfo = reply->readAll();
    //qDebug()<<searchInfo;
    QJsonParseError err;
    QJsonDocument json_recv = QJsonDocument::fromJson(searchInfo,&err);
    if(err.error != QJsonParseError::NoError){
        qDebug()<<"搜索错误";
        return;
    }
    QJsonObject totalObject = json_recv.object();
    QStringList keys = totalObject.keys();
    if(keys.contains("result"))
    {
        QJsonObject resultObject = totalObject["result"].toObject();
        QStringList resultKeys = resultObject.keys();
        if(resultKeys.contains("songs"))
        {
            QJsonArray array = resultObject["songs"].toArray();
            for(auto i:array){
                QJsonObject object = i.toObject();
                musicId = object["id"].toInt();
                musicDuration = object["duration"].toInt();
                musicName = object["name"].toString();
                mvId = object["mvid"].toInt();
                QStringList artistKeys = object.keys();
                if(artistKeys.contains("artists")){
                    QJsonArray artistArray = object["artists"].toArray();
                    for(auto j:artistArray){
                        QJsonObject object2 = j.toObject();
                        singerName = object2["name"].toString();
                        picurl = object2["img1v1Url"].toString();
                    }
                }
                if(artistKeys.contains("album")){
                    QJsonObject albumObject = object["album"].toObject();
                    albumName = albumObject["name"].toString();
                }
                music m;
                m.musicID = musicId, m.Album = albumName, m.Author = singerName, m.local = false, m.time = durationTime,
                m.title = musicName, m.url = playUrl.arg(musicId);
                v.push_back(m);
                musicId = -1;
            }
        }
    }
    emit SearchFinished(v);//发送音乐
    qDebug()<<"音乐已发送！";
    v.clear();
    qDebug()<<"=============================================网易API搜索结束=====================================";
}

