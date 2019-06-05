#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <vector>

// 创建线程
#if 0
void *EntryFunc(void *arg)
{
    (void) arg;

    while (true)
    {
        std::cout << "I am thread 1 !" << std::endl;
        sleep(1);
    }

    return nullptr;
}

int main(void)
{
    // 线程 id
    pthread_t tid;
    int ret;

    if ((ret = pthread_create(&tid, nullptr, EntryFunc, nullptr)) != 0)
    {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    // 走到这里说明线程创建成功
    while (true)
    {
        std::cout << "I am Main thread !" << std::endl;
        sleep(1);
    }

    return 0;
}
#endif

// 线程id
#if 0
void *EntryFunc(void *arg)
{
    (void)arg;
    *(pthread_t *)arg = pthread_self();

    std::cout << "Thread 1 : " << *(pthread_t*)arg << std::endl;
    return nullptr;
}


int main(void)
{
    pthread_t tid;
    pthread_t tid_1;
    pthread_create(&tid, NULL, EntryFunc, &tid_1);
    std::cout << "Main Thread:  " << tid << std::endl;

    while (true);
    return 0;
}
#endif

// 进程终止
// pthread_exit
#if 0
void *EntryFunc(void *arg)
{
    (void) arg;

    std::cout << "I am thread 1 !" << std::endl;

    pthread_exit(nullptr);

    std::cout << "Test pthread_exit ." << std::endl;

    return nullptr;
}

int main(void)
{
    pthread_t tid;
    pthread_create(&tid, nullptr, EntryFunc, nullptr);

    while (true)
    {
        sleep(1);
    }
    return 0;
}
#endif

// pthread_cancel
#if 0

std::vector<int> arr(1000000);

void *EntryFunc(void *arg)
{
    (void) arg;

    std::cout << "Assignment Start! " << std::endl;
    for(size_t i = 0; i < arr.size(); i++)
    {
        arr[i] = i;
    }
    std::cout << "Assignment Done! " << std::endl;

    return nullptr;
}

int main(void)
{
    pthread_t tid;
    pthread_create(&tid, nullptr, EntryFunc, nullptr);

    sleep(1);
    pthread_cancel(tid);
    while (true)
    {
        sleep(1);
    }
    return 0;
}
#endif

#if 0

void *ThreadEntry(void *arg)
{
    (void) arg;

    sleep(5);

    std::cout << "Thread 1 Exit" << std::endl;

    return nullptr;
}

int main(void)
{
    pthread_t tid;
    pthread_create(&tid, nullptr, ThreadEntry, nullptr);

    // 不回收线程
    while (true)
    {
        sleep(1);
    }

    return 0;
}
#endif


// pthread_join 
#if 0
void *ThreadEntry(void *arg)
{
    (void) arg;

    std::cout << "Thread 1." << std::endl;
    while (true);

    return nullptr;
}

int main(void)
{
    pthread_t tid;
    pthread_create(&tid, nullptr, ThreadEntry, nullptr);
 
    std::cout << "Main Thread." << std::endl;
    pthread_join(tid, nullptr);

    return 0;
}
#endif

#if 0
void *ThreadEntry(void *arg)
{
    while (true)
    {
        std::cout << (char *)arg << std::endl;
        sleep(1);
    }
}

int main(void)
{
    pthread_t tid;
    pthread_create(&tid, nullptr, ThreadEntry, (void*)"Thread running...");
    
    for (int i = 0; i < 5; i++)
    {
        std::cout << "Main Thread runing...." << std::endl;
        sleep(1);
    } 
    exit(1);

    return 0;
}
#endif

// 使用gdb调试多线程程序
#if 0
void *ThreadEntry(void *arg)
{
    (void)arg;

    while (true)
    {
        std::cout << "Thread 1 runnning ... " << std::endl;
        sleep(1);
    }

    return nullptr ;
}

int main(void)
{
    pthread_t tid;
    pthread_create(&tid, nullptr, ThreadEntry, nullptr);

    std::cout << "Main Thread running ...." << std::endl;

    pthread_join(tid, nullptr);

    return 0;
}
#endif

// 测试多线程提升效率
#if 1
std::vector<int> arr(500000000);
// 线程数
const int thread_num = 1;

void *ThreadEntry(void *arg)
{
    for (int i = *(int*)arg; i < *((int*)arg + 1); i++)
    {
        arr[i] = i;
    }

    return nullptr;
}
int main(void)
{
    std::vector<pthread_t> tid(thread_num);
    int space[2] = {0};
    int start = 0;
    int end = 0;
    int gap = (arr.size() / thread_num);

    int start_time = clock();
    for (size_t i = 0; i < thread_num; i++)
    {
        end = start + gap;

        space[0] = start;
        space[1] = end;
        pthread_create(&tid[i], nullptr, ThreadEntry, (void*)space);

        start = end;
    }

    for (size_t i = 0; i < thread_num; i++)
    {
        pthread_join(tid[i], 0);
    }
    int end_time = clock();

    std::cout << "Total spend: " << end_time - start_time << std::endl;

    return 0;
}

#endif
