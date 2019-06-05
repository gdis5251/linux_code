#include <iostream>
#include <pthread.h>

#if 0
// 多线程访问共有资源
int count = 0;
pthread_mutex_t mutex;

void *ThreadEntry(void *arg)
{
    (void)arg;
    
    for (int i = 0; i < 50000; i++)
    {
        pthread_mutex_lock(&mutex);
        count++;
        pthread_mutex_unlock(&mutex);
    }

    return nullptr;
}

int main(void)
{
    pthread_mutex_init(&mutex, nullptr);

    pthread_t tid1, tid2;
    pthread_create(&tid1, nullptr, ThreadEntry, nullptr);
    pthread_create(&tid2, nullptr, ThreadEntry, nullptr);

    pthread_join(tid1, nullptr);
    pthread_join(tid2, nullptr);

    pthread_mutex_destroy(&mutex);

    std::cout << count << std::endl;

    return 0;
}
#endif

#if 0
// 测试c++中的锁是否可以保证线程安全
#include <mutex>

int count = 0;
std::mutex mutex;

void *ThreadEntry(void *arg)
{
    (void)arg;
    
    for (int i = 0; i < 50000; i++)
    {
        mutex.lock();
        count++;
        mutex.unlock();
    }

    return nullptr;
}

int main(void)
{
    pthread_t tid1, tid2;
    pthread_create(&tid1, nullptr, ThreadEntry, nullptr);
    pthread_create(&tid2, nullptr, ThreadEntry, nullptr);

    pthread_join(tid1, nullptr);
    pthread_join(tid2, nullptr);

    std::cout << count << std::endl;

    return 0;
}
#endif

#if 1
#include <unistd.h>
// 同步练习
pthread_mutex_t mutex;
pthread_cond_t cond;

void *Waiter(void *arg)
{
    (void) arg;

    while (true)
    {
        std::cout << "端菜" << std::endl;

        pthread_cond_signal(&cond);

        usleep(888888);
    }

    return nullptr;
}

void *Guest(void *arg)
{
    (void) arg;

    while (true)
    {
        pthread_cond_wait(&cond, &mutex);

        std::cout << "吃饭" << std::endl;
        usleep(333333);
    }
    return nullptr;
}

int main(void)
{
    pthread_t tid1, tid2;

    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&cond, nullptr);

    pthread_create(&tid1, nullptr, Waiter, nullptr);
    pthread_create(&tid2, nullptr, Guest, nullptr);

    pthread_join(tid1, nullptr);
    pthread_join(tid2, nullptr);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}
#endif
