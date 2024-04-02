#include "Snake.h"
#include "Constants.h"

static const qreal SNAKE_SIZE = TILE_SIZE;

Snake::Snake(GameController &controller)
    : head(0, 0), growing(7), speed(5), moveDirection(NoMove),
      controller(controller) {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
}

QRectF Snake::boundingRect() const {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
  qreal minX = head.x(), minY = head.y(), maxX = head.x(), maxY = head.y();

  for (const auto &c : tail) {
    maxX = c.x() > maxX ? c.x() : maxX;
    maxY = c.y() > maxY ? c.y() : maxY;
    minX = c.x() < minX ? c.x() : minX;
    minY = c.y() < minY ? c.y() : minY;
  }

  QPointF tl = mapFromScene(QPointF(minX, minY)),
          br = mapFromScene(QPointF(maxX, maxY));

  QRectF bound = QRectF(tl.x(), tl.y(), br.x() - tl.x() + SNAKE_SIZE,
                        br.y() - tl.y() + SNAKE_SIZE);
  return bound;
}

QPainterPath Snake::shape() const {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
  QPainterPath path;
  path.setFillRule(Qt::WindingFill);

  path.addRect(QRectF(0, 0, SNAKE_SIZE, SNAKE_SIZE));

  for (const auto &c : tail) {
    auto itemp = mapFromScene(c);
    path.addRect(QRectF(itemp.x(), itemp.y(), SNAKE_SIZE, SNAKE_SIZE));
  }

  return path;
}

void Snake::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                  QWidget *) {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
  painter->save();
  painter->fillPath(shape(), Qt::yellow);
  painter->restore();
}

void Snake::setMoveDirection(Direction direction) {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
  if (moveDirection == MoveLeft && direction == MoveRight) {
    return;
  }
  if (moveDirection == MoveRight && direction == MoveLeft) {
    return;
  }
  if (moveDirection == MoveUp && direction == MoveDown) {
    return;
  }
  if (moveDirection == MoveDown && direction == MoveUp) {
    return;
  }
  moveDirection = direction;
}

Snake::Direction Snake::currentDirection() {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
  return moveDirection;
}

void Snake::advance(int step) {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
  if (!step) {
    return;
  }
  if (tickCounter++ % speed != 0) {
    return;
  }

  if (growing) {
    QPointF tailPoint = head;
    tail.emplace_back(tailPoint);
    growing--;
  } else {
    tail.removeFirst();
    tail.emplace_back(head);
  }

  switch (moveDirection) {
  case NoMove:
    return;
  case MoveLeft:
    moveLeft();
    break;
  case MoveRight:
    moveRight();
    break;
  case MoveUp:
    moveUp();
    break;
  case MoveDown:
    moveDown();
    break;
  default:
    break;
  }

  setPos(head);
  handleCollisions();
}

template <typename T> void Snake::move(T &pos, int offset, int max, int min) {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
  pos += offset;
  if (pos >= max) {
    pos = min;
  } else if (pos <= min) {
    pos = max;
  }
}

void Snake::moveLeft() {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
  move(head.rx(), -SNAKE_SIZE, 100, -100);
}

void Snake::moveRight() {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
  move(head.rx(), SNAKE_SIZE, 100, -100);
}

void Snake::moveUp() {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
  move(head.ry(), -SNAKE_SIZE, 100, -100);
}

void Snake::moveDown() {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
  move(head.ry(), SNAKE_SIZE, 100, -100);
}

void Snake::handleCollisions() {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
  QList<QGraphicsItem *> collisions = collidingItems();

  for (const auto &collidingItem : collisions) {
    if (collidingItem->data(GD_Type) == GO_Food) {
      controller.snakeAteFood((Food *)collidingItem);
      growing++;
    }
  }

  if (tail.contains(head)) {
    controller.snakeAteItself();
  }
}
