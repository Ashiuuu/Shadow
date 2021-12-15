#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "io/io.h"

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
                    printf("Reading -c argument as a stream :\n");
                    FILE *arg = string_to_stream(optarg);
                    int ch;
                    while ((ch = fgetc(arg)) != EOF)
                        printf("%c\n", ch);
                    fclose(arg);
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
