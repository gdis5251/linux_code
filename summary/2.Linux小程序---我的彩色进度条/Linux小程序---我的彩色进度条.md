# Linux小程序---我的彩色进度条

开始在linux下做一些小程序，第一个就是进度条。其实就是一个伪进度条。是根据时间来走的。

先来看一下代码：

```cpp
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define NONE                 "\e[0m"
#define BLACK                "\e[0;30m"
#define L_BLACK              "\e[1;30m"
#define RED                  "\e[0;31m"
#define L_RED                "\e[1;31m"
#define GREEN                "\e[0;32m"
#define L_GREEN              "\e[1;32m"
#define BROWN                "\e[0;33m"
#define YELLOW               "\e[1;33m"
#define BLUE                 "\e[0;34m"
#define L_BLUE               "\e[1;34m"
#define PURPLE               "\e[0;35m"
#define L_PURPLE             "\e[1;35m"
#define CYAN                 "\e[0;36m"
#define L_CYAN               "\e[1;36m"
#define GRAY                 "\e[0;37m"
#define WHITE                "\e[1;37m"

#define BOLD                 "\e[1m"
#define UNDERLINE            "\e[4m"
#define BLINK                "\e[5m"
#define REVERSE              "\e[7m"
#define HIDE                 "\e[8m"
#define CLEAR                "\e[2J"
#define CLRLINE              "\r\e[K" //or "\e[1K\r""]]"

int main(void)
{
    char bar[102] = {'\0'};
    const char *label = "|/-\\";
    int i = 0;
    char space[100];
    int j = 0;
    for (j = 0; j < 100; j++)
        space[j] = ' ';

    while (i <= 100)
    {
        if (i < 25)
            printf("\e[0;31m[\e[0m" "\e[0;31;41m%-s\e[0m" "%s" "\e[0;31m][%d%%][%c]\e[0m\r", bar, space, i, label[i % 4]);
        else if (i < 100)
            printf("\e[0;33m[\e[0m" "\e[0;33;43m%-s\e[0m" "%s" "\e[0;33m][%d%%][%c]\e[0m\r", bar, space, i, label[i % 4]);
        else
            printf("\e[0;32m[\e[0m" "\e[0;32;42m%-s\e[0m" "%s" "\e[0;32m][%d%%][%c]\e[0m\r", bar, space, i, label[i % 4]);
        
        fflush(stdout);
        space[99 - i] = '\0';
        bar[i++] = ' ';

        usleep(100000);

    }
    printf("\n");
    return 0;
}

```

**bar：**

1. 这是一个存储字符的数组，也就是我们进度条的显示内容。因为进度条一般来说是百分之一百嘛，就给他102个空间绝对够。
2. 这个数组里面先全部存’\0', 这样在打印的时候就是有多少打多少。就是把'\0'之前的内容全部打出来。每循环一次就存一个空格。其实这里存啥都行，因为后面要给背景色，存啥都会消失。除非你把字符和背景色的颜色调成不一样的，看需求吧。

**space：**

1. 这个数组用来干啥呢？试想想，如果我们直接打印```bar```数组的内容，加上颜色，直接一整行都会变色，因为我们要[  这两个中括号之间的距离始终为100  ]。如果你不加```space```数组来控制中间的无色部分，那么你就得在打印bar数组是加上```printf("[%-100s]..."...)```这样就给你弄成100个这个颜色了。覆盖了我们要显示的部分。
2. 所以```space```数组就是你```bar```多打一个有色空格,我就少打一个无色空格。来维持这100个空格内一部分有色，一部分无色。

**\r：**这个是将光标回到行首但是不换行。

**fflush(stdout):**因为缓冲区是按行刷新，或者缓冲区满了再刷新。所以我们需要手动将缓冲区的内容刷新出来。

**说了这么多，怎么让进度条有颜色呢？其实就是在printf里加上有颜色的格式就行。**

具体参考博客：[linux下printf函数显示不同颜色](https://blog.csdn.net/bloong/article/details/51576674 )

