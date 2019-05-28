# volatile 是个坑。

> volatile 关键字是告诉编译器，不要把这个变量放到寄存器里。

我们先来看一段代码：

```cpp
#include <iostream>
#include <csignal>

int flag = 1;

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

```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190528100854920.png)

当我们使用 `ctrl + c` 发送信号的时候，会将 `flag` 改为0，所以程序就不会无休止的循环下去了。

但是如果我们把编译器优化开到2，会发生什么呢？

`Makefile`

```cpp
Main:Main.cpp
	g++ -o $@ $^ -std=c++11 -O2

.PHONY:clean
clean:
	rm Main

```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190528101132739.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjY3ODUwNw==,size_16,color_FFFFFF,t_70)

我们可以看到，不管我按多少次 `ctrl + c` 程序都不会终止。

### 原因：

- 我把编译器优化开到2之后，由于while循环要频繁读取 flag 到寄存器中，编译器就会判定为这是一个  比较高的开销，另一方面，编译器没检测到有哪个代码要修改 flag（MyHandler  函数是由内核调用的，编译器并不知道），编译器就出现了错误判断，就直接把 flag 这个值优化到寄存器中。
- 所以，ctrl + c 改了flag 之后，flag并不会被读取，cpu继续读取寄存器中的 flag。

### 解决办法：

`volatile int flag = 1;`

我们在 `flag` 之前使用 `volatile` 关键字，就是告诉编译器不要把这个变量放到寄存器中，才能使程序达到我们想要的结果。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190528101722237.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjY3ODUwNw==,size_16,color_FFFFFF,t_70)

### 结论：

所以 `volatile` 关键字是一个没有办法的办法，总的来说还是编译器没办法解决这个问题，所以需要我们手动添加关键字。

叮~ :bell: