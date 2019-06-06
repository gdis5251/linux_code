#include "BlockingQueue.hpp"
#include <ctime>
#include <unistd.h>

void *Producer(void *arg)
{
    BlockingQueue<int> *p = (BlockingQueue<int> *)arg;
    srand(time(nullptr));

    while(true)
    {
        int data = rand() % 921;
        p->Push(data);

        std::cout << "Producer done. The data is --> " << data << std::endl;

        usleep(333333);
    }

    return nullptr;
}

void *Consume(void *arg)
{
    BlockingQueue<int> *p = (BlockingQueue<int> *)arg;

    while (true)
    {
        int data = p->Pop();
        
        std::cout << "Consume done. The data is --> " << data << std::endl;

        usleep(777777);
    }

    return nullptr;
}

int main(void)
{
    pthread_t tid1, tid2;
    BlockingQueue<int> bq(10);

    pthread_create(&tid1, nullptr, Producer, (void*)&bq);
    pthread_create(&tid2, nullptr, Consume, (void*)&bq);

    pthread_join(tid1, nullptr);
    pthread_join(tid2, nullptr);

    return 0;
}
