#include <iostream>
#include <unistd.h>
#include <sys/wait.h>


typedef void(*func_ptr)(int, int);

void ProcessCreate(pid_t* pid, func_ptr func, void* arg)
{
    std::cout << "Process Create!" << std::endl;

    pid_t id = fork();

    if (id == 0)//Child
    {
        func(*((int*)arg), *((int*)arg + 1));
        exit(0);
    }

    //Parent
    *pid = id;//让pid = 子进程的pid
    int status = 0;
    int ret = 0;
    while(1)//轮询方式等待子进程退出
    {
        ret = waitpid(*pid, &status, WNOHANG);
        if (ret != 0)
            break;
    }

    if (ret > 0)
    {
        std::cout << "Success Create Process!" << std::endl;
    }

    if ((status & 0xff) == 0)
    {
        status >>= 8;
        std::cout << "Child Process Normal Exit, And the Exit Code is : " << (status&0xff) << std::endl; 
    }
    else
    {
        std::cout << "Child Process Abnormal Exit, And the Signal is : " << (status & 0x7f) << std::endl;
    }
    *pid = ret;
}

void Func(int i, int j)
{
    std::cout << "I am child, And my id is : " << getpid() << std::endl;
    std::cout << i + j << std::endl;
    sleep(100);
}

int main(void)
{
    int pid = 0;
    int arg[2] = {7, 14};
    ProcessCreate(&pid, Func, (void*)&arg);

    return 0;
}
