#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Food.h"
#include <QAction>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QObject>
#include <QTimer>

class Snake;
/*
 * 初始话场景中的游戏对象，开始游戏循环。
 * 每一个游戏都需要一个游戏循环，类似于事件循环
 * */
class GameController : public QObject {
  Q_OBJECT
public:
  /*explicit*/ GameController(QGraphicsScene &scence,
                              QObject *parent = nullptr);
  ~GameController();

  void snakeAteFood(Food *food);
  void snakeAteItself();
  QAction *getResmueAction();
  void setResumeAction(QAction *r);

public slots:
  void pause();
  void resume();
  void gameOver();

  // QObject interface
public:
  bool eventFilter(QObject *watched, QEvent *event);

private:
  void handleKeyPressed(QKeyEvent *event);
  void addNewFood();
  void setResume();
  QAction *resumeAction;
  QTimer *timer;
  QGraphicsScene &scence;
  Snake *snake;
  bool isPause;
};

#endif // GAMECONTROLLER_H
