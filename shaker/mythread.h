
#ifndef MYTHREAD_H
#define MYTHREAD_H


#include <QObject>
#include <QThread>
#include <QRandomGenerator>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QThread *parent = nullptr);

public:
    void diceBegin();
    void dicePause();
    void stopThread();

signals:
    void newValue(int m_seq, int m_diceValue);

    // QThread interface
protected:
    void run();

public:
    bool m_stop, m_paused;
    int m_seq, m_diceValue;
};

#endif // MYTHREAD_H
