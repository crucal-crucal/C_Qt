
#include "mythread.h"

MyThread::MyThread(QThread *parent)
    : QThread{parent}
{

}

void MyThread::run()
{
    int cnt = 0;
    while(1)
    {
        emit curNumber(cnt++);
        if(cnt==1000000) break;
        QThread::usleep(100);
    }
}

