#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "io/io.h"
#include "parser/parser.h"
#include "lexer/lexer.h"

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
                    //struct INPUT *input = input_from_string(optarg);
                    //struct lexer *lexer = lexer_new(input);
                    //parse_input(NULL, lexer);
                    parse_input(NULL, lexer_new(input_from_string(optarg)));
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
