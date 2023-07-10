
#ifndef MY_ITEM_H
#define MY_ITEM_H


#include <QWidget>
#include <QLabel>
#include <QSize>
#include <QVector>
#include "my_music.h"

class My_Item : public QWidget
{
    Q_OBJECT
public:
    explicit My_Item(QWidget *parent = nullptr);

    My_Item(QString _music_name, QString _Author, QString _Album);
signals:

public:
    QLabel *music_name, *Author, *Album;
};

#endif // MY_ITEM_H
