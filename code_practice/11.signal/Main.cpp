#include <iostream>
#include <cassert>
#include <csignal>


void MyHandler (int signal)
{
    std::cout << "Catch a signal : " << signal << std::endl;
}

int main(void)
{
    signal(SIGINT, MyHandler);
    
    while (1)
    {
        ;
    }

    return 0;
}
