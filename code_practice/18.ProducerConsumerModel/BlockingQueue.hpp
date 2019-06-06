#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include <unistd.h>

#if 0
// 用队列和互斥量和条件变量实现阻塞队列
template <class T>
class BlockingQueue
{
public:
    BlockingQueue(int capacity)
        :_capicity(capacity)
    {
        pthread_mutex_init(&_mutex, nullptr);
        pthread_cond_init(&_full, nullptr);
        pthread_cond_init(&_empty, nullptr);
    }

    virtual ~BlockingQueue()
    {
        pthread_mutex_destroy(&_mutex);
        pthread_cond_destroy(&_full);
        pthread_cond_destroy(&_empty);
    }

    // 插入是生产者的动作
    void Push(const T data)
    {
        LockQueue();

        // 如果阻塞队列满了，就给消费者发信号
        // 让消费者拿数据
        while (IsFull())
        {
            NotifyConsume();

            std::cout << "BlockingQueue is full. Producer stop push." << std::endl;

            ProducerWait();
        }

        _qu.push(data);
        NotifyConsume();

        UnlockQueue();
    }

    // 删除是消费者的动作
    T Pop()
    {
        LockQueue();

        // 如果队列为空，给生产者发信号
        // 让生产者插入数据
        while (IsEmpty())
        {
            NotifyProducer();

            std::cout << "BlockingQueue is empty. Consume stop pop." << std::endl;

            ConsumeWait();
        }

        T ret = _qu.front();
        _qu.pop();

        NotifyProducer();

        UnlockQueue();

        return ret;
    }

private:
    void LockQueue()
    {
        pthread_mutex_lock(&_mutex);
    }

    void UnlockQueue()
    {
        pthread_mutex_unlock(&_mutex);
    }

    void ProducerWait()
    {
        pthread_cond_wait(&_full, &_mutex);
    }

    void NotifyProducer()
    {
        pthread_cond_signal(&_full);
    }

    void ConsumeWait()
    {
        pthread_cond_wait(&_empty, &_mutex);
    }

    void NotifyConsume()
    {
        pthread_cond_signal(&_empty);
    }

    bool IsEmpty()
    {
        return _qu.size() == 0 ? true : false;
    }

    bool IsFull()
    {
        return _qu.size() == _capicity ? true : false;
    }

private:
    std::queue<T> _qu;      // 用队列来实现一个阻塞队列
    pthread_mutex_t _mutex; // 锁来保证线程安全
    pthread_cond_t _full;   // 当队列满了，生产者需要等待消费者发送信号
    pthread_cond_t _empty;  // 当队列空了，消费者需要等待生产者发送信号
    int _capicity;
};
#endif

#if 1
// 用信号量和环形数组来实现阻塞队列
#include <semaphore.h>

template <class T>
class BlockingQueue
{
public:
    BlockingQueue(int capacity)
        :_head(0),
        _tail(0),
        _size(0),
        _capicity(capacity)
    {
        _qu.resize(capacity);
        sem_init(&_lock, 0, 1);
    }

    virtual ~BlockingQueue()
    {
        sem_destroy(&_lock);
    }

    void Push(const T& data)
    {
        while (IsFull())
        {
            std::cout << "BlockingQueue is full. Producer waiting..." << std::endl;
            usleep(999999);
        }

        sem_wait(&_lock);

        _qu[_tail++] = data;
        _tail %= _capicity;
        _size++;

        sem_post(&_lock);
    }

    T Pop()
    {
        while (IsEmpty())
        {
            std::cout << "BlockingQueue is empty. Consume waiting..." << std::endl;
            usleep(999999);
        }

        sem_wait(&_lock);

        T data = _qu[_head++];
        _head %= _capicity;
        _size--;

        sem_post(&_lock);

        return data;
    }

private:
    bool IsFull()
    {
        return _size == _capicity ? true : false;
    }

    bool IsEmpty()
    {
        return _size == 0 ? true : false;
    }
private:
    sem_t _lock;
    std::vector<T> _qu;
    int _head;
    int _tail;
    int _size;
    int _capicity;
};
#endif
