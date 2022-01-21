#include "parser.h"

// Grammar
// ['!'] command ('|' ('\n')* command)*
enum parser_status parse_pipeline(struct ast_node **ast, struct lexer *input)
{
    struct token *tok = lexer_peek(input);
    if (tok->type == TOKEN_ERROR)
        return TOKEN_ERROR;

    int negated = 0;

    if (tok->type == TOKEN_PIPE_NEG)
    {
        negated = 1;
        tok = lexer_pop(input);
        if (tok->type == TOKEN_ERROR)
            return TOKEN_ERROR;
    }

    struct ast_node *com = NULL;
    enum parser_status stat = parse_command(&com, input);
    if (stat != PARSER_FOUND)
        return stat;

    tok = lexer_peek(input);
    if (tok->type == TOKEN_ERROR)
    {
        free_node(com);
        return TOKEN_ERROR;
    }

    if (tok->type != TOKEN_PIPE)
    {
        *ast = com;
        return PARSER_FOUND;
    }

    lexer_pop(input);
    struct ast_node *pipe = new_pipe_node();
    pipe->data.ast_pipe.negated = negated;
    pipe->data.ast_pipe.left = com;
    *ast = pipe;

    while (1)
    {
        tok = lexer_peek(input);
        if (tok->type == TOKEN_ERROR)
        {
            free_node(*ast);
            return PARSER_ERROR;
        }

        while (tok->type == TOKEN_EOL)
        {
           tok = lexer_peek(input);
            if (tok->type == TOKEN_ERROR)
            {
                free_node(*ast);
                return PARSER_ERROR;
            } 
        }

        struct ast_node *right = NULL;
        stat = parse_command(&right, input);
        if (stat != PARSER_FOUND)
        {
            free_node(*ast);
            return PARSER_ERROR;
        }

        (*ast)->data.ast_pipe.right = right;

        tok = lexer_peek(input);
        if (tok->type == TOKEN_ERROR)
        {
            free_node(*ast);
            return PARSER_ERROR;
        }
        if (tok->type == TOKEN_PIPE)
        {
            struct ast_node *temp = *ast;
            *ast = new_pipe_node();
            (*ast)->data.ast_pipe.left = temp;
            lexer_pop(input);
        }
        else
        {
            return PARSER_FOUND;
        }
    }

    return PARSER_FOUND; // shouldn't come here
}