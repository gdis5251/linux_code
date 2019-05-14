#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    std::cout << "Process Wait Test" << std::endl;
    pid_t ret = fork();

    if (ret == 0)//child
    {
        std::cout << "I am child, And my id is : " << getpid() << std::endl;
        sleep(100);
        exit(1);
    }
    
    int status;
    int ret1 = wait(&status);

    std::cout << "I am parent, And my id is : " << getpid() << std::endl;
    std::cout << "Waited for " << ret1 << " process." << std::endl;
    if ((status & 0xff) == 0)
    {
        status >>= 8;
        std::cout << ret1 << " process exit code is :" << (status & 0xff) << std::endl; 
    }
    else
    {
        std::cout << ret1 << " process exit exception, and the signal is : " << (status & 0x7f) << std::endl;
    }
    //pid_t ret1 = fork();

    //if (ret1 == 0)//child
    //{
    //    std::cout << "I am child, And my id is : " << getpid() << std::endl;
    //    sleep(1);
    //    exit(1);
    //}


    //pid_t ret2;
    //while (1)
    //{
    //    ret2 = waitpid(ret, NULL, WNOHANG);
    //    if (ret2 != 0)
    //        break;
    //}
    //std::cout << "I am parent, And my id is : " << getpid() << std::endl;
    //std::cout << "Waited for " << ret2 << " process." << std::endl;
    //
    //pid_t ret3;
    //while (1)
    //{
    //    ret3 = waitpid(ret1, NULL, WNOHANG);
    //    if (ret3 != 0)
    //        break;
    //}
    //std::cout << "I am parent, And my id is : " << getpid() << std::endl;
    //std::cout << "Waited for " << ret3 << " process." << std::endl;

    return 0;
}
