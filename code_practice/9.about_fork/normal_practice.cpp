#include <iostream>
#include <unistd.h>
//
//int main(void)
//{
//    pid_t id = fork();
//
//    if (id > 0)//parent
//    {
//        std::cout << "I am parent. My PID is : " << getpid() << std::endl;
//    }
//    else if (id == 0)//child
//    {
//        std::cout << "I am child. My PID is : " << getpid() << std::endl;
//    }
//    else//error
//    {
//        std::cout << "bad_fork" << std::endl;
//    }
//
//    return 0;
//}

int main(void)
{
    int a = 0;

    pid_t id = fork();
    //pid_t id = vfork();

    if (id > 0)//parent
    {
        std::cout << "I am parent. My pid is : " << getpid() << "  a : " << a << std::endl;
        sleep(2);
        std::cout << "I am parent. My pid is : " << getpid() << "  a : " << a << std::endl;
    }
    else if (id == 0)
    {
        sleep(1);
        a = 2;
        std::cout << "I am child. My pid is : " << getpid() << "  a : " << a << std::endl;
        exit(0);
    }
    else
    {
        std::cout << "bad_fork" << std::endl;
    }

    return 0;
}
