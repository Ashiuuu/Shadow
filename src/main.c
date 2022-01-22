#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "exec/exec.h"
#include "interactive/interactive.h"
#include "io/io.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "printer/printer.h"
#include "variables/variables.h"
/**
 * @file main.c
 * @author Team
 * @brief 42sh project for EPITA
 * @version 1.0
 * @date 2022-01-23
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "script/file_input.h"
#include "utils/utils.h"

void as_argument(char *com, char **com_argv, int printer)
{
    struct lexer *lexer = lexer_new(input_from_string(com));
    struct token *tok = lexer_peek(lexer);

    init_positional_arguments(com_argv);

    int return_status = 0;

    while (tok->type != TOKEN_EOF)
    {
        struct ast_node *ast = NULL;
        enum parser_status stat = parse_input(&ast, lexer);
        
        if (stat == PARSER_ERROR)
        {
            free_node(ast);
            variable_push_int("?", 2);
            lexer_free(lexer);
            return;
        }
        if (printer == 1)
        {
            print_ast(ast, "");
        }
        if (ast == NULL)
            continue;
        return_status = exec_node(ast);
        free_node(ast);

        if (printer == 1)
        {
            write_file("}\n");
        }
        tok = lexer_peek(lexer);
    }


    lexer_free(lexer);
    variable_push_int("?", return_status);
}

/**
 * @brief Main function
 *
 * @param argc Number of arguments
 * @param argv Arguments
 * @return int Return status of the AST execution
 */
int main(int argc, char *argv[])
{
    variables = new_linked_list();
    init_variables();
    if (argc == 1)
    {
        interact();
    }
    else
    {
        //struct ast_node *ast = NULL;
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
            {
                file_input(argv + 1);
            }

            switch (opt)
            {
            case 'c':
                as_argument(optarg, argv + optind, printer);
                int status_code = atoi(get_linked_list(variables, "?"));
                free_linked_list(variables);
                return status_code;
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
    int status_code = atoi(get_linked_list(variables, "?"));
    free_linked_list(variables);
    return status_code;
}
