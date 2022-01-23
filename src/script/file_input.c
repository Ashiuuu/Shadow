#include "file_input.h"

#include "lexer.h"
#include "variables.h"

void file_input(char **cmd_file)
{
    init_positional_arguments(cmd_file);

    struct lexer *lexer = lexer_new(input_from_file(cmd_file[0]));
    if (lexer == NULL)
    {
        if (variables != NULL)
            free_linked_list(variables);
        fprintf(stderr, "Unable to open %s\n", cmd_file[0]);
        variable_push_int("?", 127);
        return;
    }

    struct token *tok = lexer_peek(lexer);
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

        if (ast == NULL)
            continue;
        return_status = exec_node(ast);
        free_node(ast);

        tok = lexer_peek(lexer);
    }

    variable_push_int("?", return_status);
    lexer_free(lexer);
}
