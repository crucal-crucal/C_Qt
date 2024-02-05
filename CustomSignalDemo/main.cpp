#include "SignalTest.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  SignalTest w;
  w.show();
  QObject::connect(&w, &SignalTest::signalTest, [&](const QVariant &val) {
    auto op = val.value<MyDef>();
    qDebug() << op.a;
  });
  return a.exec();
}
