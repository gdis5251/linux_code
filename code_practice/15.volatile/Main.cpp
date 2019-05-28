#include <iostream>
#include <csignal>

volatile int flag = 1;

void MyHandler(int signal)
{
    (void)signal;
    flag = 0;
    std::cout << "flag = 0, Process exit." << std::endl;
}

int main(void)
{
    signal(SIGINT, MyHandler);
    while (flag)
    {
        ;
    }

    return 0;
}
