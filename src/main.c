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

int end_with_n(char *string)
{
    size_t len = strlen(string);
    if (string[len - 1] == '\n')
        return 1;
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        //printf("not implemented yet");
        /*
        while (1)
        {
            char *ex = "exit";
            char *cmdline = xcalloc(0, 16);
            char str[16];
            printf("42sh$ ");
            while(fgets(str, sizeof(str), stdin) != NULL) 
            {
                if (*str == *ex)
                    return 0;
                //when new line --> exec cmdline
                strcat(cmdline, str);
                if (end_with_n(cmdline))
                {
                    printf("exec: %s\n", cmdline);
                    cmdline = xcalloc(0, 16);
                }
            }
            printf("fdp : %s\n", cmdline);
        }*/
        
        struct ast_node *ast = NULL;
        char *ex = "exit";
        //char *cmdline = xcalloc(0, );
        char *cmdline = xcalloc(0,2);
        printf("42sh$ ");
        char c;
        int size = 0;
        while ((c = getchar()) != EOF)
        {
            if (c == '\n')
            {
                size = 0;
                if (strcmp(cmdline, ex) == 0)
                    return 0;
                parse_input(&ast, lexer_new(input_from_string(cmdline)));
                exec_node(ast);
                free_node(ast);
                free(cmdline);
                cmdline = xcalloc(0, 2);
                printf("42sh$ ");
                continue;
            }
            xrealloc(cmdline, size + 2);
            cmdline[size] = c;
            cmdline[size + 1] = '\0';
            size += 1;
        } 
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
                    free_node(ast);

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
