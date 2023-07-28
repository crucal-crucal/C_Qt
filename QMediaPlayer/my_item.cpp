
#include "my_item.h"

My_Item::My_Item(QWidget *parent)
    : QWidget{parent}
{
}

My_Item::My_Item(QString _music_name, QString _Author, QString _Album)
{
    music_name = new QLabel(this);
    music_name->setText(_music_name);
    music_name->setAlignment(Qt::AlignCenter);
    music_name->move(0, 0);

    Author = new QLabel(this);
    Author->setText(_Author);
    Author->setAlignment(Qt::AlignCenter);
    Author->move(this->width()/2, 0);

    Album = new QLabel(this);
    Album->setText(_Album);
    Album->setAlignment(Qt::AlignCenter);
    Album->move(this->width(), 0);
}

