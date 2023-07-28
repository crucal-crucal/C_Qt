
#include "widget.h"

#include <QApplication>
#include <QSqlDatabase>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Widget w;
  qDebug() << QSqlDatabase::drivers();
  w.show();
  return a.exec();
}
