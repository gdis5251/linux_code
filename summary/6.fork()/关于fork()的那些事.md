# 关于fork()的那些事:artificial_satellite:

## fork()是什么？有什么用？

- fork()是一个系统调用函数。
- fork()的返回值是一个整形。并且不需要只能和参数。
- 在Linux下，fork()包含在`#include <unistd.h>`这个头文件中，Linux中的大部分系统调用都在这个头文件里面。
- fork()可以创建一个子进程，使父子进程可以继续执行fork()后的代码。
- fork()是一次调用两次返回，对父进程返回子进程的`pid`，对子进程返回0。如果调用失败则返回负数。

我们来看一个代码说明这个问题：

```cpp
#include <iostream>
#include <unistd.h>

int main(void)
{
    pid_t id = fork();

    if (id > 0)//parent
    {
        std::cout << "I am parent. My PID is : " << getpid() << std::endl;
    }
    else if (id == 0)//child
    {
        std::cout << "I am child. My PID is : " << getpid() << std::endl;
    }
    else//error
    {
        std::cout << "bad_fork" << std::endl;
    }

    return 0;
}

```

![1](F:\linux_code\summary\6.fork()\1.png)

fork()之后就有了两个进程，继续执行fork()后面的代码。

## fork()的运行规则

- 以父进程为模板创建子进程。
- 会把父进程的PCB拷贝一份，稍加修改称为自己的PCB。
- 会把父进程的地址空间拷贝一份，成为子进程的地址空间。
- fork()返回会在父子进程分别返回，在fork()后继续往下执行。
- 父子进程的执行顺序没有先后顺序，全靠调度器调度。

## fork()的写时拷贝

创建一个子进程，如果说直接拷贝父进程的PCB和地址空间，往往开销比较大，所以，fork()经过过年的演化，衍生出了一种写时拷贝的规则。就是说，fork()之后，会拷贝父进程的PCB，和地址空间的某些东西。像不改变的东西，就共用一份就行。比如说，代码一般不可改变，因为代码段是只读的（但还是有某种方法可以改变，不然外挂是怎么工作的），所以父子进程的地址空间里的代码段就指向内存中的同一份代码。只有某一放发生改变的时候，子进程才会拷贝一份代码自己用。**数据也是一样的，只不过数据容易被改变，我们思想默认都是直接拷贝数据。**

通常情况下，父子进程共用同一份代码，各自有一份数据。由于大部分内存空间可能被拷贝，创建进程开销仍然比较高。（和线程相比）

## fork()调用失败的原因

我们先看看Linux的man手册是怎么说的：

![2](F:\linux_code\summary\6.fork()\2.png)

就两点失败的原因：

1. 系统的进程太多了，没有足够的资源来创建新的进程。
2. 内存不够了。

## fork()的兄弟---vfork()

`vfork()`和`fork()`的作用是一样的，也是创建子进程。它跟`fork()`的不同在于：

- `vfork()`保证了创建子进程后，子进程先运行。
- `vfork()`创建子进程后，父子进程共享地址空间。

我们来对比一下：

先来看看`fork()`的效果：

```cpp
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

```

![3](F:\linux_code\summary\6.fork()\3.png)

子进程修改了变量a，无论父进程是在子进程前运行还是在子进程后运行，它都显示`a == 0`，所以我们推断出，父子进程发生写时拷贝后，各自有一份变量。

那么再来看看`vfork()`：

```cpp
int main(void)
{
    int a = 0;

    //pid_t id = fork();
    pid_t id = vfork();

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

```

![4](F:\linux_code\summary\6.fork()\4.png)

首先就是，`vfork()`保证了子进程先运行，父进程等着子进程运行完了再运行。

然后，父子进程共享地址空间，子进程修改了变量a后，相当有父进程指向的变量也会改变。

