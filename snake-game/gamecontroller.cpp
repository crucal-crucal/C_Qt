#include "gamecontroller.h"
#include "food.h"
#include "snake.h"
#include <QAction>
#include <QEvent>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMessageBox>
#include <iostream>

#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
#include <QRandomGenerator>
#endif

GameController::GameController(QGraphicsScene &scene, QObject *parent)
    : QObject(parent), scene(scene), snake(new Snake(*this)), isPause(false) {
  timer.start(1000 / 33);

  Food *a1 = new Food(0, -50);
  scene.addItem(a1);

  scene.addItem(snake);
  scene.installEventFilter(this);
  // resume();
  //    connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
  connect(&timer, &QTimer::timeout, &scene, &QGraphicsScene::advance);
  isPause = false;
}

GameController::~GameController() {}

void GameController::snakeAteFood(Food *food) {
  scene.removeItem(food);

  addNewFood();
}

void GameController::snakeAteItself() {
  //    QTimer::singleShot(0, this, SLOT(gameOver()));
  QTimer::singleShot(0, this, &GameController::gameOver);
}

void GameController::handleKeyPressed(QKeyEvent *event) {
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
  int x, y;
  do {
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
    QRandomGenerator generator;
    x = (int)(generator.generate() % 200) / 10 - 10;
    y = (int)(generator.generate() % 200) / 10 - 10;
#else
    x = (int)qrand() % 200 / 10 - 10;
    y = (int)qrand() % 200 / 10 - 10;
    x *= 10;
    y *= 10;
#endif
  } while (snake->shape().contains(snake->mapFromScene(QPointF(x + 5, y + 5))));

  Food *food = new Food(x, y);
  scene.addItem(food);
}

void GameController::gameOver() {
  //    disconnect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
  disconnect(&timer, &QTimer::timeout, &scene, &QGraphicsScene::advance);
  if (QMessageBox::Yes ==
      QMessageBox::information(NULL, tr("Game Over"), tr("Again?"),
                               QMessageBox::Yes | QMessageBox::No,
                               QMessageBox::Yes)) {
    //        connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
    connect(&timer, &QTimer::timeout, &scene, &QGraphicsScene::advance);
    scene.clear();

    snake = new Snake(*this);
    scene.addItem(snake);
    addNewFood();
  } else {
    exit(0);
  }
}

void GameController::pause() {
  //    disconnect(&timer, SIGNAL(timeout()),
  //               &scene, SLOT(advance()));
  disconnect(&timer, &QTimer::timeout, &scene, &QGraphicsScene::advance);
  isPause = true;
  setResume();
}

void GameController::resume() {
  //    connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
  connect(&timer, &QTimer::timeout, &scene, &QGraphicsScene::advance);
  isPause = false;
  setResume();
}

void GameController ::setResume() {
  if (isPause == true) {
    resumeAction->setEnabled(true);
  } else {
    resumeAction->setEnabled(false);
  }
}

bool GameController::eventFilter(QObject *object, QEvent *event) {
  if (event->type() == QEvent::KeyPress) {
    handleKeyPressed((QKeyEvent *)event);
    return true;
  } else {
    return QObject::eventFilter(object, event);
  }
}
