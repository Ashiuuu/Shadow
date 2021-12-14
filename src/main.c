#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <getopt.h>

int main(int argc, char* argv[])
{
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
            switch(opt)
            {
                case 'c':
                    printf("%s\n", optarg);
                    // exec optarg command
                    // exit
                    break;
                case '?':
                    if (optopt == 'c')
                        printf("Option -c needs an argument\n");
                    else
                        printf("Unknown option character");
                    break;
                default:
                    printf("error");
                    abort();
            }
        }
    }

    return 0;
}
