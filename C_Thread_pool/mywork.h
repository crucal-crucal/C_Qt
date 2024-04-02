
#ifndef MYWORK_H
#define MYWORK_H


#include <QObject>
#include <QThreadPool>
#include <QRunnable>

class MyWork : public QRunnable
{

protected:
    void run() override;
};

#endif // MYWORK_H
