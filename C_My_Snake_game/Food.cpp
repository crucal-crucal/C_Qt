#include "Food.h"
#include "Constants.h"

static const qreal FOOD_RADIUS = 3.0;

Food::Food(qreal x, qreal y) {
  this->setPos(x, y);
  this->setData(GD_Type, GO_Food);
}

// 返回一个简单的矩形
// 范围实际是四倍于实际区域的：已坐标元素（x, y）为中心，边长为 TILE_SIZE << 1
// 的简单矩形
QRectF Food::boundingRect() const {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
  return QRectF(-TILE_SIZE, -TILE_SIZE, TILE_SIZE << 1, TILE_SIZE << 1);
}

// 把shape函数定义的路径画出来
void Food::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                 QWidget *widget) {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
  Q_UNUSED(option);
  Q_UNUSED(widget);
  painter->save();

  painter->setRenderHint(QPainter::Antialiasing);
  painter->fillPath(shape(), Qt::red);

  painter->restore();
}

// 返回元素实际路径
QPainterPath Food::shape() const {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
  QPainterPath p;
  // 添加一个圆心为 TILE_SIZE >> 1 ， 半径为 FOOD_RADIUS 的圆
  p.addEllipse(QPointF(TILE_SIZE >> 1, TILE_SIZE >> 1), FOOD_RADIUS,
               FOOD_RADIUS);
  return p;
}
