#include <iostream>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <cstring>

ssize_t WriteFile()
{
    int fd = open("Test.txt", O_WRONLY | O_CREAT);
    if (fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char buf[1024] = "I Will Get BAT Offer!\n";
    ssize_t count = write(fd, buf, strlen(buf));

    close(fd);

    return count;
}

ssize_t ReadFile()
{
    int fd = open("Test.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    
    char buf[1024] = {0};
    ssize_t count = read(fd, buf, sizeof(buf) - 1);
    buf[count] = 0;

    std::cout << buf << std::endl;

    return count;
}
int main(void)
{
    WriteFile();

    ReadFile();

    return 0;
}


