
#ifndef MYWORK_H
#define MYWORK_H


#include <QObject>
#include <QThread>

class MyWork : public QObject
{
    Q_OBJECT
public:
    explicit MyWork(QObject *parent = nullptr);

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
};

#endif // MYWORK_H
