# 使用gdb调试多线程程序

在我们日常打代码的日子里，肯定会涉及到多线程的程序，那么在Linux下编写多线程的程序应该如何调试呢。

```cpp
void *ThreadEntry(void *arg)
{
    (void)arg;

    while (true)
    {
        std::cout << "Thread 1 runnning ... " << std::endl;
        sleep(1);
    }

    return nullptr ;
}

int main(void)
{
    pthread_t tid;
    pthread_create(&tid, nullptr, ThreadEntry, nullptr);

    std::cout << "Main Thread running ...." << std::endl;

    pthread_join(tid, nullptr);

    return 0;
}
```

就比如这样一个代码，我们应该如何调试？

- 首先通过`ps aux | grep Main`命令找到进程的`pid`。

- 然后再通过`gdb attach pid`附加到已经运行到的进程中。（如果是在程序运行前调试，可以直接`gdb 进程名`的方式进入调试）

- 然后通过`info thread`查看当前所有线程列表和当前所在线程。

  ![在这里插入图片描述](https://img-blog.csdnimg.cn/20190601172822220.png)

- 可以用过`thread 数字`（就是上图线程对应的数字）的方式切换当前线程。

  ![在这里插入图片描述](https://img-blog.csdnimg.cn/20190601173044388.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjY3ODUwNw==,size_16,color_FFFFFF,t_70)

- 之后你就可以使用日常gdb调试手段来调试多线程啦。

叮~:bell: