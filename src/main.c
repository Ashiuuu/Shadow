#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        printf("sh$ ");
        int fd = 0; // 0 = stdin
        char buf[32];
        read(fd, buf, 31);
        printf("%s", buf);
        printf("%s", argv);
    }
    else
    {
        printf("exec some command");
    }
    return 0;
}
