
#ifndef MYTHREAD_H
#define MYTHREAD_H


#include <QObject>
#include <QThread>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QThread *parent = nullptr);

signals:
    void curNumber(int cnt);

    // QThread interface
protected:
    void run();

};

#endif // MYTHREAD_H
