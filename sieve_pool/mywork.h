<<<<<<< HEAD

#ifndef MYWORK_H
#define MYWORK_H


#include <QObject>
#include <QRunnable>
#include <QThread>

class MyWork : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit MyWork(QThread *parent = nullptr);

public:
    void working();
    void diceBegin();
    void dicePause();
    void stopThread();

signals:
    void newValue(int m_seq, int m_diceValue);

public:
    bool m_paused = false, m_stop = false;
    int m_diceValue, m_seq;

    // QRunnable interface
public:
    void run();
};

#endif // MYWORK_H
=======

#ifndef MYWORK_H
#define MYWORK_H


#include <QObject>
#include <QRunnable>
#include <QThread>

class MyWork : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit MyWork(QThread *parent = nullptr);

public:
    void working();
    void diceBegin();
    void dicePause();
    void stopThread();

signals:
    void newValue(int m_seq, int m_diceValue);

public:
    bool m_paused = false, m_stop = false;
    int m_diceValue, m_seq;

    // QRunnable interface
public:
    void run();
};

#endif // MYWORK_H
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
