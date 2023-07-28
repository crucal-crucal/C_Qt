#include "QMyThreadPool.h"

#include <QThreadPool>

//==============================================example====================================================/
work1::work1(QObject *parent) : QObject{parent}, QRunnable{} {
  this->setAutoDelete(true); // start automatic destruction this class object.
}

void work1::run() {
  // we must write our code in this run function
  qDebug() << "This is a example !";

  emit exampleSignal(9999); // we can use this signal to send our messge to main
                            // thread objects or other objects
}
//=========================================================================================================/
