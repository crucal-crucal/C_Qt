#include "gamecontroller.h"
#include "food.h"
#include "snake.h"
#include <QAction>
#include <QEvent>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMessageBox>
#include <QRandomGenerator>
#include <iostream>

GameController::GameController(QGraphicsScene &scence, QObject *parent)
    : QObject(parent), scence(scence), snake(new Snake(*this)), isPause(false) {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
  timer = new QTimer(this);
  timer->start(1000 / 33);

  Food *a1 = new Food(0, -50);
  scence.addItem(a1);

  scence.addItem(snake);
  scence.installEventFilter(this);
  // resume();
  connect(timer, &QTimer::timeout, &scence, &QGraphicsScene::advance);
  isPause = false;
}

GameController::~GameController() {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
}

void GameController::snakeAteFood(Food *food) {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
  scence.removeItem(food);

  addNewFood();
}

void GameController::snakeAteItself() {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
  QTimer::singleShot(0, this, &GameController::gameOver);
}

QAction *GameController::getResmueAction() {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
  return resumeAction;
}

void GameController::setResumeAction(QAction *r) {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
  resumeAction = r;
}

void GameController::handleKeyPressed(QKeyEvent *event) {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
  if (!isPause)
    switch (event->key()) {
    case Qt::Key_Left:
      snake->setMoveDirection(Snake::MoveLeft);
      break;
    case Qt::Key_Right:
      snake->setMoveDirection(Snake::MoveRight);
      break;
    case Qt::Key_Up:
      snake->setMoveDirection(Snake::MoveUp);
      break;
    case Qt::Key_Down:
      snake->setMoveDirection(Snake::MoveDown);
      break;
    case Qt::Key_Space:
      pause();
      break;
    }
  else
    resume();
}

void GameController::addNewFood() {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
  int x, y;
  QRandomGenerator generator;
  do {
    x = (int)(generator.generate() % 200) / 10 - 10;
    y = (int)(generator.generate() % 200) / 10 - 10;

    x *= 10;
    y *= 10;
  } while (snake->shape().contains(snake->mapFromScene(QPointF(x + 5, y + 5))));

  Food *food = new Food(x, y);
  scence.addItem(food);
}

void GameController::gameOver() {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
  disconnect(timer, SIGNAL(timeout()), &scence, SLOT(advance()));
  delete timer;
  if (QMessageBox::Yes ==
      QMessageBox::information(NULL, tr("Game Over"), tr("Again?"),
                               QMessageBox::Yes | QMessageBox::No,
                               QMessageBox::Yes)) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, &scence, &QGraphicsScene::advance);
    scence.clear();

    snake = new Snake(*this);
    scence.addItem(snake);
    addNewFood();
  } else {
    exit(0);
  }
}

void GameController::pause() {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
  disconnect(timer, &QTimer::timeout, &scence, &QGraphicsScene::advance);
  isPause = true;
  setResume();
}

void GameController::resume() {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
  connect(timer, &QTimer::timeout, &scence, &QGraphicsScene::advance);
  isPause = false;
  setResume();
}
void GameController ::setResume() {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
  if (isPause == true) {
    resumeAction->setEnabled(true);
  } else {
    resumeAction->setEnabled(false);
  }
}
bool GameController::eventFilter(QObject *object, QEvent *event) {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
  if (event->type() == QEvent::KeyPress) {
    handleKeyPressed((QKeyEvent *)event);
    return true;
  } else {
    return QObject::eventFilter(object, event);
  }
}
