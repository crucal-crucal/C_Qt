
#ifndef MYNETWORK_H
#define MYNETWORK_H


#include <QObject>
#include <QtMultimedia>
#include <QUrl>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QNetworkAccessManager>
#include <QTextBlock>
#include <QNetworkReply>
#include <QJsonArray>
#include <QJsonObject>
#include <QVector>
#include "my_music.h"

class MyNetWork : public QObject
{
    Q_OBJECT
public:
    explicit MyNetWork(QObject *parent = nullptr);
    void search(QString keywords);

signals:
    void SearchFinished(QVector<music>);

public slots:
    void DataBack(QNetworkReply *reply);//解析音乐

private:
    //网易接口
    QString front ="http://music.163.com/api/search/get/web?csrf_token=hlpretag=&hlposttag=&s={";
    QString back = "}&type=1&offset=0&total=true&limit=30";//接入网易云API并且传入需要搜索的数据和返回的数量
    //完整搜索 url = front + 关键字 + back;  ----- limit:搜索返回的歌曲数量

    QString playUrl = QString("http://music.163.com/song/media/outer/url?id=%1.mp3");
    //完整播放url = QString("http://music.163.com/song/media/outer/url?id=%1.mp3").arg(音乐id);

    int downPos;
    QString durationTime;//播放时间
    QString positionTime;//
    QNetworkAccessManager *manager;//网络管家
    QString file;
    QTextDocument *doc;
    QTextBlock textLine;
    QString str;
    int i,x;
    int musicId,musicDuration,mvId;
    QString musicName,sigerName,albumName;
    QString picurl;
    QString singerName;
    QVector<music> v;
};

#endif // MYNETWORK_H
