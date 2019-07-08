#include "singleton_pattern.hpp"
#include <thread>

void ThreadEntry(int n)
{
    std::cout << Singleton::GetInstance() << std::endl;
}

int main(void)
{
    std::thread t1(ThreadEntry, 10);
    std::thread t2(ThreadEntry, 10);

    t1.join();
    t2.join();

    std::cout << Singleton::GetInstance() << std::endl;
    std::cout << Singleton::GetInstance() << std::endl;
}
