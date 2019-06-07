#pragma once
#include <iostream>
#include "BlockingQueue.hpp"

class Task
{
public:
    virtual void Run()
    {
        std::cout << "Base Run" << std::endl;
    }

    virtual ~Task()
    {
    }
};

// 线程池对象启动的时候会创建一组线程
// 每个线程都会完成一定的任务(执行一定的代码逻辑, 这个逻辑是由调用者来决定)
//
// 任务是一段代码，就可以用函数来表示
class ThreadPool
{
public:
    ThreadPool(int n) 
        :qu_(100),
        woker_(n)
    {
        // 创建出若干个线程
        for (int i = 0; i < n; i++)
        {
            pthread_t tid;
            pthread_create(&tid, nullptr, ThreadEntry, this);
            wokers_.push_back(tid);
        }
    }
    ~ThreadPool()
    {
        // 让线程退出，然后再回收
        for (size_t i = 0; i < wokers_.size(); i++)
        {
            pthread_cancel(wokers_[i]);
        }
        for (size_t i = 0; i < wokers_.size(); i++)
        {
            pthread_join(wokers_[i], nullptr);
        }
    }

    // 使用线程池的时候就需要由调用者加入一些任务
    // 让线程去执行
    void AddTask(Task *task)
    {
        qu_.Push(task);
    }
private:
    BlockingQueue<Task*> qu_;
    int woker_;
    std::vector<pthread_t> wokers_;

private:
    static void *ThreadEntry(void *arg)
    {
        ThreadPool *pool = (ThreadPool *)arg;

        while (true)
        {
            // 循环中尝试从阻塞队列中获取到一个任务
            // 就执行一个任务
            Task *task = nullptr;
            pool->qu_.Pop(&task);

            task->Run();
            delete task;
        }

        return nullptr;
    }
};

