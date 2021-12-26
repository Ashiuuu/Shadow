#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "io/io.h"
#include "parser/parser.h"
#include "lexer/lexer.h"
#include "exec/exec.h"

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
                case 'c': ;
                    struct ast_node *ast = NULL;
                    parse_input(&ast, lexer_new(input_from_string(optarg)));
                    exec_node(ast);
                    return 0;
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
