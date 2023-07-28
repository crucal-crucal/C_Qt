
#ifndef MY_MUSIC_H
#define MY_MUSIC_H

#include <QUrl>
#include <QString>


class music{
public:
    QUrl url;//播放路径
    QString title;//音乐名称
    QString Author;//作者
    QString Album;//专辑
    QString wordsPath;//歌词路径
    QString time;//时间
    qint32 musicID;//记录歌曲的标识
    qint32 index;//播放列表里的索引
    bool local;//本地为true
    bool m_Type;
    QString pictrue;
    music(QUrl _QUrl,QString _Author,QString _title);
    music(QString _title,QString _Author,QString _Album, QString _time);
    music(){}
    bool operator==(const music &x)const{
        if(this->musicID == x.musicID)
            return true;
        return false;
    }
    bool operator=(const music m){
        this->musicID = m.musicID;
        this->Album = m.Album;
        this->Author = m.Author;
        //this->index = m.index;
        this->m_Type = m.m_Type;
        this->time = m.time;
        this->title = m.title;
        this->url = m.url;
        this->wordsPath = m.wordsPath;
        this->pictrue = m.pictrue;
        this->local = m.local;
        return true;
    }
};

#endif // MY_MUSIC_H
