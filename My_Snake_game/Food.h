#ifndef FOOD_H
#define FOOD_H
// #define NDEBUG
#include <QGraphicsItem>
#include <QObject>
#include <QPainter>

class Food : public QGraphicsItem {
public:
  /*explicit*/ Food(qreal x, qreal y);

  // QGraphicsItem interface
public:
  QRectF boundingRect() const;
  QPainterPath shape() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget);
};

#endif // FOOD_H
