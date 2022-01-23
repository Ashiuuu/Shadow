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
}
