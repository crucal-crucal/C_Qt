
#include "mywork.h"

MyWork::MyWork(QObject *parent)
    : QObject{parent}
{

}

void MyWork::diceBegin()
{ //开始掷骰子
    m_paused=false;
}

void MyWork::dicePause()
{//暂停掷骰子
    m_paused=true;
}

void MyWork::stopThread()
{//停止线程
    m_stop=true;
}

void MyWork::working()
{
    //线程的事件循环
    m_seq = 0;            //掷骰子次数
    while(!m_stop)      //循环主体
    {
        if (!m_paused)
        {
            m_diceValue= rand()%6+1; //产生随机数[1,6]
            m_seq++;
            emit newValue(m_seq, m_diceValue);  //发射信号
        }
        QThread::msleep(500);    //线程休眠500ms
    }
}

