#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GameController.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>
#include <QMenu>
#include <QMessageBox>
#include <QPixmap>
#include <QTimer>

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void createAction();
  void createMenus();

  void initScence();
  void initScenceBackground();

private slots:
  void adjustViewSize();
  void newGame();
  void gameHelp();
  void about();

private:
  QGraphicsScene *scence;
  QGraphicsView *view;

  GameController *game;

  QAction *newGameAction;
  QAction *pauseAction;
  QAction *resumeAction;
  QAction *exitAction;
  QAction *gameHelpAction;
  QAction *aboutAction;
  QAction *aboutQtAction;
};
#endif // MAINWINDOW_H
