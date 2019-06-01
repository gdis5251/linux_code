# Linux线程控制​

> 线程控制的相关函数不是系统调用是库函数。
>
> 线程控制的函数库是POSIX线程库。
>
> POSIX是一个标准，规定了操作系统需要写哪些接口供程序员来使用。
>
> 与线程有关的函数大多数都是以`pthread_`开头的。
>
> 需要使用线程函数库的时候需要引入头文件 `<pthread>`，并且因为该库是一个动态库，在写编译命令的时候需要在后面加上 `-lpthread`链接这个库。

## 创建线程

### pthread_create

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190531154038421.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjY3ODUwNw==,size_16,color_FFFFFF,t_70)

首先这个函数有四个参数，我先来说一下每个**参数**都代表着什么：

- thread: 这是一个输出型参数，就是你传进去一个`pthread_t tid`这个类型的变量，然后它给你返回你创建的这个线程的线程 id。（`pthread_t`是一个`unsigned long`类型 ）
- attr: 设置线程的属性，如果你并不关注它的属性，你就设置为 `NULL`就表示使用默认属性。
- start_routine: 这是一个函数指针，就是你创建出来的线程，你希望它干什么，就传一个函数进去。这个比创建进程方便多了，创建进程的话，如果你希望创建出来的进程干别的事情，还需要进行进程程序替换。
- arg: 这个就是你上一个函数所需要的参数。

**返回值**：

- 如果成功返回0，如果失败返回错误码。

### 一个简单的进程创建程序

```cpp
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>

void *EntryFunc(void *arg)
{
    (void) arg;

    while (true)
    {
        std::cout << "I am thread 1 !" << std::endl;
        sleep(1);
    }

    return nullptr;
}

int main(void)
{
    // 线程 id
    pthread_t tid;
    int ret;

    if ((ret = pthread_create(&tid, nullptr, EntryFunc, nullptr)) != 0)
    {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    // 走到这里说明线程创建成功
    while (true)
    {
        std::cout << "I am Main thread !" << std::endl;
        sleep(1);
    }

    return 0;
}

```

![在这里插入图片描述](https://img-blog.csdnimg.cn/2019053116063477.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjY3ODUwNw==,size_16,color_FFFFFF,t_70)

**从这个程序我们可以得出几条性质：**

- 进程是抢占式调度的，从打印结果可以看出，并没有什么顺序可言。

- 可以通过 `pstack 进程id` 这条命令看到线程调用栈。

  ![在这里插入图片描述](https://img-blog.csdnimg.cn/20190531160932917.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjY3ODUwNw==,size_16,color_FFFFFF,t_70)

- 从线程调用栈可以看出来，创建线程的系统调用是 `clone()`。

## 认识线程ID

线程id有两个！对你没有听错。站在不同角度看，线程id就不一样。

先来看一段代码：

```cpp
void *EntryFunc(void *arg)
{
    (void)arg;
    *(pthread_t *)arg = pthread_self();

    std::cout << *(pthread_t*)arg << std::endl;
    return nullptr;
}


int main(void)
{
    pthread_t tid;
    pthread_t tid_1;
    pthread_create(&tid, NULL, EntryFunc, &tid_1);
    std::cout << tid << std::endl;

    return 0;
}

```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190531163150434.png)

这里我们看到，打印出来的线程id是一个很大的数字，其实他是一个地址。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190531163729583.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjY3ODUwNw==,size_16,color_FFFFFF,t_70)

虚拟地址空间里，有一段区域叫做共享内存。这个里面就存放着除主线程之外其他线程的一些信息，而我们通过创建线程得到的线程id就是指向它本身信息的地址。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190531164037668.png)

可是我们通过 `ps -eLf | grep Main | grep -v grep`命令看到的 `LWP`线程id是通过系统调度角度，看到的线程id。因为线程也是一个轻量级进程，需要被调度，所以它需要一个唯一标识来让操作系统去调度它。

## 线程终止

线程有一个非常BUG的地方就是，当某一个线程异常终止了，那么整个进程就异常终止。

如果我们需要让线程正常结束而不影响整个进程的话，有已下三种方式：

- 从线程函数return， 这种方法对主线程不适用（主线程就是哪个包含main函数的线程），从main函数return就相当于调用exit，使整个进程终止。
- 线程可以调用`pthread_exit`来终止自己。
- 一个线程可以通过调用`pthread_cancel`终止同一进程中的另一个线程。

### pthread_exit

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190531165133407.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjY3ODUwNw==,size_16,color_FFFFFF,t_70)

**参数：**

- `value_ptr`这个参数表示线程结束的返回结果，但是这个参数很少用到，所以我下面会填`nullptr`。

这个函数就是在线程的入口函数里调用的，是让线程自己终止自己，而不会触发异常或使整个进程退出。

```cpp
void *EntryFunc(void *arg)
{
    (void) arg;

    std::cout << "I am thread 1 !" << std::endl;

    pthread_exit(nullptr);

    std::cout << "Test pthread_exit ." << std::endl;

    return nullptr;
}

int main(void)
{
    pthread_t tid;
    pthread_create(&tid, nullptr, EntryFunc, nullptr);

    while (true)
    {
        sleep(1);
    }
    return 0;
}

```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190531165739394.png)

从现象我们可以看出来，线程的入口函数明明有两个打印的语句，但是只打印了一句话，因为在打印第二句话之前我调用了`pthread_exit()`函数让线程退出了，并且我的主线程还依然存在没有退出。

### pthread_cancel

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190531170152227.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjY3ODUwNw==,size_16,color_FFFFFF,t_70)

**参数：**

- `thread`是本进程中，想要结束的线程的id。

**返回值：**

- 成功返回0， 失败返回错误码。

这是一个比较鸡肋的函数，因为它可能会破坏线程的事务性。

> 事务性：要求具有“原子性”，要么就做完，要么就不做，千万不能半途而废，如果半途而废就可能导致数据被破坏。

我们可以看下面这个代码：

```cpp

std::vector<int> arr(1000000);

void *EntryFunc(void *arg)
{
    (void) arg;
    
    std::cout << "Assignment Start! " << std::endl;
    for(size_t i = 0; i < arr.size(); i++)
    {
        arr[i] = i;
        sleep(1);
    }
    std::cout << "Assignment Done! " << std::endl;

    return nullptr;
}

int main(void)
{
    pthread_t tid;
    pthread_create(&tid, nullptr, EntryFunc, nullptr);

    sleep(1);
    pthread_cancel(tid);
    while (true)
    {
        sleep(1);
    }
    return 0;
}

```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190531171844891.png)

不管等多久，`Assignment Done！`都不会打印，因为主线程把那个线程终止了，这就导致线程1正在修改数据，可是被终止了，所以这个数据就会出现错误。这就破坏了该线程的事务性。

可是如果我把线程1里面的`sleep(1)`去掉：

```cpp
void *EntryFunc(void *arg)
{
    (void) arg;
    
    std::cout << "Assignment Start! " << std::endl;
    for(size_t i = 0; i < arr.size(); i++)
    {
        arr[i] = i;
        // sleep(1);
    }
    std::cout << "Assignment Done! " << std::endl;

    return nullptr;
}
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190531172144748.png)

居然，完整结束了，这到底是为什么呢？

`pthread_cancel`不会立即结束线程，如果该线程是一个CPU密集型的线程，OS会等到该线程结束CPU密集部分或者遇到阻塞/睡眠，才会结束进程。

但是这个操作是OS来做的，不能完全保证事务性，所以这个函数还是要谨慎使用。

## 线程等待

首先为什么要进行线程等待？

- 类似于进程等待，如果线程结束但是主线程没有对退出的线程进行回收，那么这个线程就会一直存在，在进程的地址空间内。
- 每个线程在进程的虚拟地址空间中的共享区都会有一份自己的信息，如果线程退出不回收，那么其他线程就不会复用退出线程的地址空间，有可能造成后期无法再创建新的线程。

### pthread_join

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190601163547496.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjY3ODUwNw==,size_16,color_FFFFFF,t_70)

**参数**：

- thread：线程id。
- retval：它指向一个指针，后者指向线程的返回值。
  1. 如果thread线程通过return返回,retval所指向的单元里存放的是thread线程函数的返回值。
  2. 如果thread线程被别的线程调用pthread_ cancel异常终掉,retval所指向的单元里存放的是常数PTHREAD_ CANCELED。
  3. 如果thread线程是自己调用pthread_exit终止的,retval所指向的单元存放的是传给pthread_exit的参数。
  4. 如果对thread线程的终止状态不感兴趣,可以传NULL给value_ ptr参数。

调用这个函数一般不关注线程的返回结果，其实是为了等待线程结束然后继续执行程序的逻辑。

这个函数是一个阻塞等待函数，程序如果调用这个函数，就会一直阻塞在这里，直到有线程结束。

```cpp
void *ThreadEntry(void *arg)
{
    (void) arg;

    std::cout << "Thread 1." << std::endl;
    while (true);

    return nullptr;
}

int main(void)
{
    pthread_t tid;
    pthread_create(&tid, nullptr, ThreadEntry, nullptr);
 
    std::cout << "Main Thread." << std::endl;
    pthread_join(tid, nullptr);

    return 0;
}
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190601164640200.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjY3ODUwNw==,size_16,color_FFFFFF,t_70)

通过`pstack 进程id`可以看到主线程阻塞在了 `pthread_join`处。

**线程等待其中一个应用场景**：

如果主线程需要等待所有其他线程运行完进程汇总的话，就可以使用线程等待他可以确保所有的线程都运行完，自己在汇总，

## 分离线程

分离线程就很像信号那篇博客里说的：子进程退出后会给父进程发送一个信号`SIGCHLD`，但是我们可以通过`signal`系统调用进行信号捕捉，然后忽略掉它。

这样就可以解决子进程退出，父进程没有回收而造成的僵尸进程的问题。

> - 默认情况下，新创建的线程是需要被等待的，如果不对其进行`pthread_join`操作，就无法释放资源，造成系统内存泄漏。
> - 但是如果我们并不关注线程的返回值，`pthread_join`就会是一个降低效率的操作，因为它是阻塞等待。所以当我们将不关心返回值的线程分离，当线程退出时，线程会自动释放。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190601170111927.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjY3ODUwNw==,size_16,color_FFFFFF,t_70)

**参数**：

- thread：线程id。

如果希望分离自己可以这样操作。

`pthread_detach(pthread_self())`

**有一个思考：如果将一个线程分离出去了，进程退出了，分离出去的线程还会跑吗？**

```cpp
void *ThreadEntry(void *arg)
{
    while (true)
    {
        std::cout << (char *)arg << std::endl;
        sleep(1);
    }
}

int main(void)
{
    pthread_t tid;
    pthread_create(&tid, nullptr, ThreadEntry, (void*)"Thread running...");
    
    for (int i = 0; i < 5; i++)
    {
        std::cout << "Main Thread runing...." << std::endl;
        sleep(1);
    } 
    exit(1);

    return 0;
}
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190601171036607.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjY3ODUwNw==,size_16,color_FFFFFF,t_70)

结果如上，不管线程是不是分离出去，只要进程退出，线程还是会退出。

因为创建出来的线程的信息在进程的地址空间中保存着，当进程退出，虚拟地址空间会被释放，所以线程自然也就退出了。

叮~:bell:

