#include "interactive.h"

#include "lexer.h"
#include "variables.h"

void interact()
{
    struct lexer *lexer = lexer_new(input_from_stdin());

    struct token *tok = lexer_peek(lexer);
    int return_status = 0;

    while (tok->type != TOKEN_EOF)
    {
        struct ast_node *ast = NULL;
        enum parser_status stat = parse_input(&ast, lexer);

        if (stat == PARSER_ERROR)
        {
            free_node(ast);
            variable_push_int("?", return_status);
            lexer_free(lexer);
            return;
        }

        if (ast == NULL)
            continue;
        return_status = exec_node(ast);
        free_node(ast);

        tok = lexer_peek(lexer);
    }

    variable_push_int("?", return_status);
    lexer_free(lexer);

    /*struct ast_node *ast = NULL;
    char *cmdline = xcalloc(0, sizeof(char));
    printf("42sh$ ");
    char c;
    int size = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == '\n')
        {
            if (strcmp(cmdline, "\0") == 0 || strcmp(cmdline, "") == 0)
            {
                printf("42sh$ ");
                continue;
            }
            size = 0;
            parse_input(&ast, lexer_new(input_from_string(cmdline)));
            exec_node(ast);
            free_node(ast);
            printf("42sh$ ");
            continue;
        }
        cmdline = xrealloc(cmdline, (size + 2));
        cmdline[size] = c;
        cmdline[size + 1] = '\0';
        size += 1;
    }
    free(cmdline);*/
}
