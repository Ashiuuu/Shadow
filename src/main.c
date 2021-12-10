#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>

int main(int argc, char* argv[])
{
    printf("argc = %d\nargv = %s\n", argc, argv);
    if (argc == 1)
    {
        printf("not implemented yet");
        // detect if something in stdin
        // display '42sh$ ' and wait for command
        // use readline for every command
    }
    else
    {
        int opt;

        while ((opt = getopt(argc, argv, "c:")) != -1)
        {
            printf("%c\n", opt);
            switch(opt)
            {
                case 'c':
                    printf("%s", optarg);
                    // exec optarg command
                    // exit
                    break;
                default:
                    printf("error");
            }
        }
    }

    return 0;
}
