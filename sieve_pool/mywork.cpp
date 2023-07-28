<<<<<<< HEAD


#include "mywork.h"

MyWork::MyWork(QThread *parent)
    : QObject{parent}, QRunnable{}
{
    this->setAutoDelete(true);//如果设置为true，那么当前的任务执行完成过后，线程池就会自动销毁当前线程
    // 不需要再手动销毁
}

void MyWork::diceBegin()
{ //开始掷骰子
    m_paused=true;
}

void MyWork::dicePause()
{//暂停掷骰子
    m_paused=true;
}

void MyWork::stopThread()
{//停止线程
    m_stop=true;
}

void MyWork::run()
{
    //线程的事件循环
    m_stop=false;       //启动线程时令m_stop=false
    m_paused=true;      //启动运行后暂时不掷骰子
    m_seq=0;            //掷骰子次数
    while(!m_stop)      //循环主体
    {
        if (!m_paused)
        {
            //m_diceValue= QRandomGenerator::global()->bounded(1,7);  //产生随机数[1,6]
            m_diceValue = rand()%6+1;
            m_seq++;
            emit newValue(m_seq, m_diceValue);  //发射信号
        }
        QThread::msleep(200);    //线程休眠200ms
    }

    //  在  m_stop==true时结束线程任务
//    QThread::quit();    //相当于exit(0), 退出线程的事件循环
//    exit(0);
}


//void MyWork::working()
//{
//    //线程的事件循环
//    m_seq = 0;            //掷骰子次数
//    while(!m_stop)      //循环主体
//    {
//        if (!m_paused)
//        {
//            m_diceValue= rand()%6+1; //产生随机数[1,6]
//            m_seq++;
//            emit newValue(m_seq, m_diceValue);  //发射信号
//        }
//        QThread::msleep(500);    //线程休眠500ms
//    }
//}

=======


#include "mywork.h"

MyWork::MyWork(QThread *parent)
    : QObject{parent}, QRunnable{}
{
    this->setAutoDelete(true);//如果设置为true，那么当前的任务执行完成过后，线程池就会自动销毁当前线程
    // 不需要再手动销毁
}

void MyWork::diceBegin()
{ //开始掷骰子
    m_paused=true;
}

void MyWork::dicePause()
{//暂停掷骰子
    m_paused=true;
}

void MyWork::stopThread()
{//停止线程
    m_stop=true;
}

void MyWork::run()
{
    //线程的事件循环
    m_stop=false;       //启动线程时令m_stop=false
    m_paused=true;      //启动运行后暂时不掷骰子
    m_seq=0;            //掷骰子次数
    while(!m_stop)      //循环主体
    {
        if (!m_paused)
        {
            //m_diceValue= QRandomGenerator::global()->bounded(1,7);  //产生随机数[1,6]
            m_diceValue = rand()%6+1;
            m_seq++;
            emit newValue(m_seq, m_diceValue);  //发射信号
        }
        QThread::msleep(200);    //线程休眠200ms
    }

    //  在  m_stop==true时结束线程任务
//    QThread::quit();    //相当于exit(0), 退出线程的事件循环
//    exit(0);
}


//void MyWork::working()
//{
//    //线程的事件循环
//    m_seq = 0;            //掷骰子次数
//    while(!m_stop)      //循环主体
//    {
//        if (!m_paused)
//        {
//            m_diceValue= rand()%6+1; //产生随机数[1,6]
//            m_seq++;
//            emit newValue(m_seq, m_diceValue);  //发射信号
//        }
//        QThread::msleep(500);    //线程休眠500ms
//    }
//}

>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
