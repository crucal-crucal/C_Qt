#include <QApplication>
#include <QDesktopWidget>

#include "Src/include/mainwindow.h"
// #define VERSION

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  MainWindow w;

#ifdef VERSION
  QDesktopWidget* desktop = QApplication::desktop();
  int desw = desktop->width();
  int desh = desktop->height();
  int scrw = w.width();
  int scrh = w.height();
  int x = (desw - scrw) >> 1;
  int y = (desh - scrh) >> 1;
  w.move(x, y);
#endif
  w.show();
  return a.exec();
}
