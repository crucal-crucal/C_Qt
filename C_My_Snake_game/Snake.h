#ifndef SNAKE_H
#define SNAKE_H

#include "GameController.h"
#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QRectF>

class GameController;

class Snake : public QGraphicsItem {
public:
  // 移动状态
  enum Direction { NoMove, MoveLeft, MoveRight, MoveUp, MoveDown };

  explicit Snake(GameController &controller);
  void setMoveDirection(Direction direction);
  Direction currentDirection();

  // QGraphicsItem interface
public:
  QRectF boundingRect() const;
  QPainterPath shape() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget);

protected:
  void advance(int step);

private:
  template <typename T> void move(T &pos, int offset, int max, int min);
  void moveLeft();
  void moveRight();
  void moveUp();
  void moveDown();

  void handleCollisions();

  QPointF head;
  int growing;
  int speed;
  int tickCounter;
  QList<QPointF> tail;
  Direction moveDirection;
  GameController &controller;
};

#endif // SNAKE_H
