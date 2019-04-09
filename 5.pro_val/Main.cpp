#include <iostream>
#include <unistd.h>

int g_val = 100;

int main(void)
{
    pid_t id = fork();

    if (id == 0)
    {
        g_val = 20;
        std::cout << "I am child! " << "pid : " << getpid() << " g_val : " << g_val << " &g_val : " << &g_val << std::endl;
        sleep(1);
    }
    else
    {
        sleep(3);
        std::cout << "I am parent! " << "pid : " << getpid() << " g_val : " << g_val << " &g_val : " << &g_val << std::endl;
        sleep(1);
    }

    return 0;
}
