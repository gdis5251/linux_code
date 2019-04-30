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
