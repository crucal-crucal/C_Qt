
#include "QMyThreadPool.h"

QMyThreadPool::QMyThreadPool(size_t num): is_running(true)
{
    for (size_t i = 0; i < num; ++i)
    {
        threads.emplace_back([this]() //创建线程
        {
            /********************************子线程***********************************************/
            while (true)
            {
                std::function<void()> task;//任务模版，存放任务的副本
                {
                    std::unique_lock<std::mutex> lock(this->mutex);//为其上锁，防止其他线程竞争，如果锁正在被使用则阻塞此线程。匿名函数执行完后自动释放锁
                    this->cv.wait(lock, [this]() //等待通知并进行条件判断后 决定是否向下执行。如果不满足条件则阻塞本线程
                    {
                        return !this->is_running || !this->tasks.empty();
                        //如果线程池在运行或则任务队列有任务则继续向下执行
                    });
                    if (!this->is_running && this->tasks.empty()) return; //如果线程池结束运行并且任务队列没有任务了就终止该线程
                    task = std::move(this->tasks.front());//向任务队列里取一个任务
                    this->tasks.pop();//弹出任务
                }
                task();//运行任务
            }
            /**************************************************************************************/
        });
    }
}
QMyThreadPool::~QMyThreadPool()
{
    {
        //匿名函数{}
        std::unique_lock<std::mutex> lock(mutex);
        is_running = false;//将线程池状态置false,后面通知所有线程结束做准备
    }
    cv.notify_all();//通知所有线程结束
    for (auto &thread : threads)
    {
        thread.join();//等待此线程执行完毕后并回收资源
    }
}

//template<typename Func, typename Args>
//void QMyThreadPool::enqueue(Func &&func, Args &&... args)
//{

//}
template<typename Func, typename... Args>
void QMyThreadPool::enqueue(Func &&func, Args &&... args)
{
    auto task = std::bind(std::forward<Func>(func), std::forward<Args>(args)...); //将函数和其参数绑定在一起后给task,forward<> 类型转发函数模版
    {
        std::unique_lock<std::mutex> lock(mutex);//上锁
        tasks.emplace(task);//将绑定好的任务放入任务队列
        //执行完此匿名函数后会自动释放互斥锁
    }
    cv.notify_one();//通知某个线程，有新任务
}


















