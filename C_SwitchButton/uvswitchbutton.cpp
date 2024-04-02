#include "uvswitchbutton.h"

#include <QPainter>

CUVSwitchButton::CUVSwitchButton(QWidget* parent) : QWidget(parent) {
  m_space = 2;
  m_radius = 5;
  m_checked = false;
  m_showText = true;
  m_showText = false;
  m_animation = true;

  m_bgColorOn = Qt::green;
  m_bgColorOff = QColor(128, 128, 128);

  m_sliderColorOn = Qt::white;
  m_sliderColorOff = Qt::white;

  m_textColor = Qt::black;

  // m_textOn = "开启";
  // m_textOff = "关闭";

  m_step = 0;
  m_startX = 0;
  m_endX = 0;

  m_timer = new QTimer(this);
  m_timer->setInterval(30);
  connect(m_timer, SIGNAL(timeout()), this, SLOT(updateValue()));
}

void CUVSwitchButton::drawBackGround(QPainter* painter) {
  painter->save();
  painter->setPen(Qt::NoPen);

  QColor bgColor = m_checked ? m_bgColorOn : m_bgColorOff;
  if (isEnabled()) {
    bgColor.setAlpha(60);
  }

  painter->setBrush(bgColor);

  QRect rect(0, 0, width(), height());
  int side = qMin(width(), height());

  // 左侧半圆
  QPainterPath path1;
  path1.addEllipse(rect.x(), rect.y(), side, side);

  // 右侧半圆
  QPainterPath path2;
  path2.addEllipse(rect.width() - side, rect.y(), side, side);

  // 中间的矩形
  QPainterPath path3;
  path3.addRect(rect.x() + side / static_cast<qreal>(2), rect.y(),
                rect.width() - side, height());

  QPainterPath path = path1 + path2 + path3;
  painter->drawPath(path);

  // 绘制文本

  // 滑块半径
  int sliderWidth = qMin(height(), width()) - m_space * 2 - 5;
  if (m_checked) {
    QRect textRect(0, 0, width() - sliderWidth, height());
    painter->setPen(QPen(m_textColor));
    painter->drawText(textRect, Qt::AlignCenter, m_textOn);
  } else {
    QRect textRect(sliderWidth, 0, width() - sliderWidth, height());
    painter->setPen(QPen(m_textColor));
    painter->drawText(textRect, Qt::AlignCenter, m_textOff);
  }

  painter->restore();
}

void CUVSwitchButton::drawSlider(QPainter* painter) {
  painter->save();
  painter->setPen(Qt::NoPen);

  QColor color = m_checked ? m_sliderColorOn : m_sliderColorOff;

  painter->setBrush(QBrush(color));

  int sliderWidth = qMin(width(), height()) - m_space * 2;
  QRect rect(m_space + m_startX, m_space, sliderWidth, sliderWidth);
  painter->drawEllipse(rect);

  painter->restore();
}

void CUVSwitchButton::paintEvent(QPaintEvent* ev) {
  // 启用反锯齿
  QPainter painter(this);
  painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

  // 绘制背景
  drawBackGround(&painter);

  // 绘制滑块
  drawSlider(&painter);
}

void CUVSwitchButton::mousePressEvent(QMouseEvent* ev) {
  Q_UNUSED(ev)

  m_checked = !m_checked;
  emit statusChanged(m_checked);

  // 计算步长
  m_step = width() / 10;

  // 计算滑块X轴终点坐标
  if (m_checked) {
    m_endX = width() - height();
  } else {
    m_endX = 0;
  }

  // 判断是否使用动画
  if (m_animation) {
    m_timer->start();
  } else {
    m_startX = m_endX;
    update();
  }
}

void CUVSwitchButton::updateValue() {
  if (m_checked) {
    if (m_startX < m_endX) {
      m_startX += m_step;
    } else {
      m_startX = m_endX;
      m_timer->stop();
    }
  } else {
    if (m_startX > m_endX) {
      m_startX -= m_step;
    } else {
      m_startX = m_endX;
      m_timer->stop();
    }
  }

  update();
}

int CUVSwitchButton::space() const { return m_space; }

int CUVSwitchButton::radius() const { return m_radius; }

bool CUVSwitchButton::checked() const { return m_checked; }

bool CUVSwitchButton::showText() const { return m_showText; }

bool CUVSwitchButton::showCircel() const { return m_showCircle; }

bool CUVSwitchButton::animation() const { return m_animation; }

QColor CUVSwitchButton::bgColorOn() const { return m_bgColorOn; }

QColor CUVSwitchButton::bgColorOff() const { return m_bgColorOff; }

QColor CUVSwitchButton::sliderColorOn() const { return m_sliderColorOn; }

QColor CUVSwitchButton::sliderColorOff() const { return m_sliderColorOff; }

QColor CUVSwitchButton::textColor() const { return m_textColor; }

QString CUVSwitchButton::textOn() const { return m_textOn; }

QString CUVSwitchButton::textOff() const { return m_textOff; }

int CUVSwitchButton::step() const { return m_step; }

int CUVSwitchButton::startX() const { return m_startX; }

int CUVSwitchButton::endX() const { return m_endX; }

void CUVSwitchButton::setSpace(int space) {
  if (m_space != space) {
    m_space = space;
    update();
  }
}

void CUVSwitchButton::setRadius(int radius) {
  if (m_radius != radius) {
    m_radius = radius;
    update();
  }
}

void CUVSwitchButton::setChecked(bool checked) {
  if (m_checked != checked) {
    m_checked = checked;
    update();
  }
}

void CUVSwitchButton::setShowText(bool show) {
  if (m_showText != show) {
    m_showText = show;
    update();
  }
}

void CUVSwitchButton::setShowCircle(bool show) {
  if (m_showCircle != show) {
    m_showCircle = show;
    update();
  }
}

void CUVSwitchButton::setAnimation(bool ok) {
  if (m_animation != ok) {
    m_animation = ok;
    update();
  }
}

void CUVSwitchButton::setBgColorOn(const QColor& color) {
  if (m_bgColorOn != color) {
    m_bgColorOn = color;
    update();
  }
}

void CUVSwitchButton::setBgColorOff(const QColor& color) {
  if (m_bgColorOff != color) {
    m_bgColorOff = color;
    update();
  }
}

void CUVSwitchButton::setSliderColorOn(const QColor& color) {
  if (m_sliderColorOn != color) {
    m_sliderColorOn = color;
    update();
  }
}

void CUVSwitchButton::setSliderColorOff(const QColor& color) {
  if (m_sliderColorOff != color) {
    m_sliderColorOff = color;
    update();
  }
}

void CUVSwitchButton::setTextColor(const QColor& color) {
  if (m_textColor != color) {
    m_textColor = color;
    update();
  }
}

void CUVSwitchButton::setTextOn(const QString& text) {
  if (m_textOn != text) {
    m_textOn = text;
    update();
  }
}

void CUVSwitchButton::setTextOff(const QString& text) {
  if (m_textOff != text) {
    m_textOff = text;
    update();
  }
}
