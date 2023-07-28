<<<<<<< HEAD
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
=======
#include "QMyThreadPool.h"

#include <QThreadPool>

//==============================================example====================================================/
work1::work1(QObject *parent): QObject{parent},QRunnable{}
{
    this->setAutoDelete(true);//start automatic destruction this class object.

}
void work1::run()
{
    //we must write our code in this run function
    qDebug()<<"This is a example !";

    emit exampleSignal(9999);//we can use this signal to send our messge to main thread objects or other objects
}
//=========================================================================================================/


>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
