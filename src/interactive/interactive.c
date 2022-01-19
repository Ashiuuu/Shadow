#include "interactive.h"

void interact()
{
    struct ast_node *ast = NULL;
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
    free(cmdline);
}