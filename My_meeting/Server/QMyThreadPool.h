<<<<<<< HEAD

#ifndef QMYTHREADPOOL_H
#define QMYTHREADPOOL_H

#include <QDebug>
#include <QObject>
#include <QRunnable>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>

/*@Brief
 * 此为一个线程池，用于处理服务器并发任务，如多个客户端申请数据，或对多个客户端发送数据
 * 防止单个线程任务过重导致程序崩溃
 * */

// Qt线程池
class QMyThreadPool : public QObject, public QRunnable {
  Q_OBJECT
public:
  explicit QMyThreadPool(QObject *parent = nullptr);

  // QRunnable interface
public:
  void run();
};

// C++线程池

// class QMyThreadPool
//{
// public:
//     explicit QMyThreadPool(size_t num = 2);//构造时制定线程数量
//     ~QMyThreadPool();
//     template<typename Func, typename... Args> //模版 ，(typename...
//     Args)模版参数列表，可容纳多个参数 void enqueue(Func &&func, Args&&...
//     args); //Args&&... 确保参数类型和值不会被修改，匹配作用

// private:
//     std::vector<std::thread> threads;//线程池
//     std::queue<std::function<void()>> tasks;//任务队列 std::function<void()>
//     函数对象类型，存储函数的方法(副本) std::mutex
//     mutex;//互斥锁，防止多个线程竞争同一资源 std::condition_variable
//     cv;//同步原语，实现线程间的条件变量等待和通知 bool
//     is_running;//判断线程池是否工作

//};

#endif // QMYTHREADPOOL_H
=======

#ifndef QMYTHREADPOOL_H
#define QMYTHREADPOOL_H


#include <QObject>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
/*@Brief
 * 此为一个线程池，用于处理服务器并发任务，如多个客户端申请数据，或对多个客户端发送数据
 * 防止单个线程任务过重导致程序崩溃
 * */

class QMyThreadPool
{
public:
    explicit QMyThreadPool(size_t num = 2);//构造时制定线程数量
    ~QMyThreadPool();
    template<typename Func, typename... Args> //模版 ，(typename... Args)模版参数列表，可容纳多个参数
    void enqueue(Func &&func, Args&&... args); //Args&&... 确保参数类型和值不会被修改，匹配作用

private:
    std::vector<std::thread> threads;//线程池
    std::queue<std::function<void()>> tasks;//任务队列     std::function<void()> 函数对象类型，存储函数的方法(副本)
    std::mutex mutex;//互斥锁，防止多个线程竞争同一资源
    std::condition_variable cv;//同步原语，实现线程间的条件变量等待和通知
    bool is_running;//判断线程池是否工作

};

#endif // QMYTHREADPOOL_H
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
