#include "mainwindow.h"
#include "qmenubar.h"

#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), scence(new QGraphicsScene(this)),
      view(new QGraphicsView(scence, this)),
      game(new GameController(*scence, this)) {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
  // 设置场景
  this->setCentralWidget(view);
  this->setWindowIcon(QIcon(":/snake.ico"));
  this->setFixedSize(600, 600);

  //
  createAction(), createMenus();
  // 初始化场景以及背景
  initScence(), initScenceBackground();

  // 在下一次事件循环开始时，立刻调用adjustViewSize函数
  // 在0ms之后调用adjustViewSize()函数
  QTimer::singleShot(0, this, &MainWindow::adjustViewSize);
}

MainWindow::~MainWindow() {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
}

void MainWindow::adjustViewSize() {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
  view->fitInView(scence->sceneRect(), Qt::KeepAspectRatioByExpanding);
}

void MainWindow::initScence() {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
  this->scence->setSceneRect(-100, -100, 200, 200);
}

void MainWindow::initScenceBackground() {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
  QPixmap background(10, 10);
  QPainter p(&background);
  p.setBrush(QBrush(Qt::gray));
  p.drawRect(0, 0, 10, 10);

  view->setBackgroundBrush(QBrush(background));
}

void MainWindow::createAction() {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
  newGameAction = new QAction("New Game", this);
  newGameAction->setShortcuts(QKeySequence::New);
  newGameAction->setStatusTip("Start a new game");
  connect(newGameAction, &QAction::triggered, this, &MainWindow::newGame);

  exitAction = new QAction("Exit", this);
  exitAction->setShortcut(tr("Ctrl+Q"));
  exitAction->setStatusTip("Exit the game");
  connect(exitAction, &QAction::triggered, this, &MainWindow::close);

  pauseAction = new QAction("Pause", this);
  pauseAction->setToolTip("Pause...");
  connect(pauseAction, &QAction::triggered, game, &GameController::pause);

  resumeAction = new QAction("Resume", this);
  resumeAction->setToolTip("Pause");
  resumeAction->setEnabled(false);
  game->setResumeAction(resumeAction);
  connect(pauseAction, &QAction::triggered, game, &GameController::resume);

  gameHelpAction = new QAction("Game Help", this);
  gameHelpAction->setShortcut(tr("Ctrl+H"));
  gameHelpAction->setStatusTip("Help on this Game");
  connect(gameHelpAction, &QAction::triggered, this, &MainWindow::gameHelp);

  aboutAction = new QAction("About", this);
  aboutAction->setStatusTip("Show the application's about box");
  connect(aboutAction, &QAction::triggered, this, &MainWindow::about);

  aboutQtAction = new QAction("About Qt", this);
  aboutQtAction->setStatusTip("Show the Qt library's About box");
  connect(aboutQtAction, &QAction::triggered, qApp, QApplication::aboutQt);
}

void MainWindow::createMenus() {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
  QMenu *options = menuBar()->addMenu(tr("&Options"));
  options->addAction(newGameAction);
  options->addSeparator();
  options->addAction(pauseAction);
  options->addAction(resumeAction);
  options->addSeparator();
  options->addAction(exitAction);

  QMenu *help = menuBar()->addMenu(tr("&Help"));
  help->addAction(gameHelpAction);
  help->addAction(aboutAction);
  help->addAction(aboutQtAction);
}

void MainWindow::newGame() {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
  QTimer::singleShot(0, game, &GameController::gameOver);
}

void MainWindow::about() {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
  QMessageBox::about(this, tr("About this Game"),
                     tr("<h2>Snake Game</h2>"
                        "<p>Copyright &copy; XXX."
                        "<p>This game is a small Qt application. It is based "
                        "on the demo in the GitHub written by Devbean."));
}

void MainWindow::gameHelp() {
#ifdef NDEBUG
  qDebug() << __func__ << "is Already running";
#endif
  QMessageBox::about(
      this, tr("Game Help"),
      tr("Using direction keys to control the snake to eat the food"
         "<p>Space - pause & resume"));
}
