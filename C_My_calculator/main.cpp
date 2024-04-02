<<<<<<< HEAD

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
=======

#include "widget.h"

#include <QApplication>
#include <QSqlDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    qDebug()<<QSqlDatabase::drivers();
    w.show();
    return a.exec();
}
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
