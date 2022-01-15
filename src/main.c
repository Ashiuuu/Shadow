#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "exec/exec.h"
#include "io/io.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "printer/printer.h"
#include "utils/utils.h"

int main(int argc, char *argv[])
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
        struct ast_node *ast = NULL;
        int printer = 0;
        while (1)
        {
            static struct option long_options[] = {
                { "code", required_argument, 0, 'c' },
                { "help", no_argument, 0, '?' },
                { "pretty_print", no_argument, 0, 'p' },
                { 0, 0, 0, 0 }
            };

            int opt = getopt_long(argc, argv, "c:p?", long_options, NULL);
            if (opt == -1)
                break;

            switch (opt)
            {
            case 'c':
                parse_input(&ast, lexer_new(input_from_string(optarg)));
                if (printer == 1)
                {
                    print_ast(ast, "");
                }
                exec_node(ast);

                if (printer == 1)
                {
                    write_file("}\n");
                }
                return 0;
                break;
            case '?':
                if (optopt == 'c')
                    printf("Option -c needs an argument\n");
                else
                    printf("Unknown option character\n");
                break;
            case 'p':
                printer = 1;
                printf("dot -Tpdf tree.dot -o tree.pdf; evince tree.pdf\n");
                write_file("graph {\n\"42sh\" -- ");
                break;
            default:
                printf("error\n");
                abort();
            }
        }
    }

    return 0;
}