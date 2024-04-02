<<<<<<< HEAD

#ifndef MYTHREAD_H
#define MYTHREAD_H


#include <QObject>
#include <QThread>
#include <QRunnable>
#include <QRandomGenerator>

class MyThread : public QObject, public QRunnable
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

public:
    // QRunnable interface
    void run();

public:
    bool m_stop, m_paused;
    int m_seq, m_diceValue;
};

#endif // MYTHREAD_H
=======

#ifndef MYTHREAD_H
#define MYTHREAD_H


#include <QObject>
#include <QThread>
#include <QRunnable>
#include <QRandomGenerator>

class MyThread : public QObject, public QRunnable
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

public:
    // QRunnable interface
    void run();

public:
    bool m_stop, m_paused;
    int m_seq, m_diceValue;
};

#endif // MYTHREAD_H
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
