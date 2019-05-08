#include <iostream>
#include <unistd.h>

//int main(void)
//{
//    std::cout << "Here is two process:" << std::endl;
//
//    pid_t id = fork();
//    if (id < 0)
//    {
//        return 1;
//    }
//
//    if (id == 0)//子进程
//    {
//        std::cout << "I am child ! My name is: " << getpid() << "  My parent name is: " << getppid() << std::endl;
//        sleep(5);
//    }
//    else //父进程
//    {
//        std::cout << "I am Parent ! My name is: " << getpid() << "  My parent name is: " << getppid() << std::endl;
//        
//        //父进程一直循环造成子进程成为僵尸进程
//        while (true)
//        {}
//    }
//
//    return 0;
//}

int main(void)
{
    std::cout << "Here is Orphan process !" << std::endl;

    pid_t id = fork();
    if (id < 0)
        return 1;

    if (id == 0)//子进程
    {
        while (true)
        {
            std::cout << "I am child ! My name is: " << getpid() << "  My parent name is: " << getppid() << std::endl;
            sleep(3);
        }
    }
    else //父进程
    {
        std::cout << "I am parent ! My name is: " << getpid() << "  My parent name is: " << getppid() << std::endl;
        sleep(3);
    }

    return 0;
}
