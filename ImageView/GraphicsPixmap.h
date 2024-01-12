#ifndef GRAPHICSPIXMAP_H
#define GRAPHICSPIXMAP_H

#include <QObject>
#include <QGraphicsObject>
#include <QPixmap>
#include <QGraphicsSceneContextMenuEvent>
#include <QPainter>
#include <QCursor>

class GraphicsPixmap : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit GraphicsPixmap();

signals:

};

#endif // GRAPHICSPIXMAP_H
