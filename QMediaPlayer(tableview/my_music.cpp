
#include "my_music.h"

music::music(QUrl _QUrl, QString _Author, QString _title)
{
    this->url = _QUrl, this->Author = _Author, this->title = _title;
}

music::music(QString _title, QString _Author, QString _Album, QString _time)
{
    this->title = _title, this->Author = _Author, this->Album = _Album, this->time = _time;
}
