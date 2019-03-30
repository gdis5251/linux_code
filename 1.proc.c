#include <stdio.h>
#include <unistd.h>
#include <string.h>


int main(void)
{
    char bar[102] = {'\0'};
    const char *label = "|/-\\";
    int i = 0;

    while (i <= 100)
    {
        printf("[%-100s][%d%%][%c]\r", bar, i, label[i % 4]);
        fflush(stdout);
        bar[i++] = '#';
        usleep(10000);

    }
    printf("\n");
    return 0;
}
