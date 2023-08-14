<<<<<<< HEAD
<<<<<<< HEAD
#ifndef QMYTHREADPOOL_H
#define QMYTHREADPOOL_H

#include <QDebug>
#include <QObject>
#include <QRunnable>
#include <QThread>

/*@brief
 * This is a thread pool,we can write some works in this class,and define our
 * signals to connect the main thread. Please reference my example (work1) to
 * write your code and take a class name that is easy to understand. use method:
 * QThreadPool::globalInstance()->start(work);//work is work1's object
 * */

class work1 : public QObject, public QRunnable {
  Q_OBJECT
public:
  explicit work1(QObject *parent = nullptr);
  void run();

signals:
  void exampleSignal(int);
};
//-----------------------------------------------------------------------------------------------------------------//

#endif // QMYTHREADPOOL_H
=======
=======
>>>>>>> 47b8f66 (update)
#ifndef QMYTHREADPOOL_H
#define QMYTHREADPOOL_H

#include <QObject>
#include <QRunnable>
#include <QThread>
#include <QDebug>

/*@brief
 * This is a thread pool,we can write some works in this class,and define our signals to connect the main thread.
 * Please reference my example (work1) to write your code and take a class name that is easy to understand.
 * use method: QThreadPool::globalInstance()->start(work);//work is work1's object
 * */

class work1 : public QObject , public QRunnable
{
    Q_OBJECT
public:
    explicit work1(QObject *parent = nullptr);
    void run();

signals:
    void exampleSignal(int);

};
//-----------------------------------------------------------------------------------------------------------------//





#endif // QMYTHREADPOOL_H
<<<<<<< HEAD
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
=======
>>>>>>> 47b8f66 (update)
