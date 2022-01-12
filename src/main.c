#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


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
        //while ((opt = getopt(argc, argv, "c:")) != -1)
        //while ((opt = getopt_long(argc, argv, "chp:", long_options, NULL)) != -1)
        while(1)
        {
            static struct option long_options[] = {
                {"code",         required_argument,        0, 'c'},
                {"help",         no_argument,  0, '?'},
                {"pretty_print", optional_argument,  0, 'p'},
                {0, 0, 0, 0}
            };

            opt = getopt_long(argc, argv, "c:p::?", long_options, NULL);
            if (opt == -1)
                break;

            switch(opt)
            {
                case 'c':
                    ;
                    struct ast_node *ast = NULL;
                    parse_input(&ast, lexer_new(input_from_string(optarg)));
                    exec_node(ast);
                    return 0;
                    break;
                case '?':
                    if (optopt == 'c')
                        printf("Option -c needs an argument\n");
                    else
                        printf("Unknown option character\n");
                    break;
                case 'p':
                    ;
                    int fd = open("tree.dot", O_CREAT | O_APPEND | O_RDWR, 0777);
                    write(fd, "graph {\n\"42sh\";\n", 27);
                    /*;
                    struct ast_node *ast = NULL;
                    parse_input(&ast, lexer_new(input_from_string(optarg)));*/

                    write(fd, "}\n", 2);
                    close(fd);
                    break;
                default:
                    printf("error\n");
                    abort();
            }
        }
    }

    return 0;
}
