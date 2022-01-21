#include "parser.h"

// Grammar:
// pipeline (('&&'|'||') ('\n')* pipeline)*
enum parser_status parse_and_or(struct ast_node **ast, struct lexer *input)
{
    struct token *tok = lexer_peek(input);
    if (tok->type == TOKEN_ERROR)
        return PARSER_ERROR;

    struct ast_node *com = NULL;
    enum parser_status stat = parse_pipeline(&com, input);
    if (stat != PARSER_FOUND)
        return stat;

    tok = lexer_peek(input);
    if (tok->type == TOKEN_ERROR)
    {
        free_node(com);
        return PARSER_ERROR;
    }

    *ast = com;
    while (tok->type == TOKEN_AND || tok->type == TOKEN_OR)
    {
        (*ast) = new_and_or_node(tok->type);
        (*ast)->data.ast_and_or.left = com;

        tok = lexer_pop(input);
        if (tok->type == TOKEN_ERROR)
        {
            free_node(*ast);
            return PARSER_ERROR;
        }

        while (tok->type == TOKEN_EOL)
        {
            tok = lexer_pop(input);
            if (tok->type == TOKEN_ERROR)
            {
                free_node(*ast);
                return PARSER_ERROR;
            }
        }

        struct ast_node *other = NULL;
        stat = parse_pipeline(&other, input);
        if (stat != PARSER_FOUND)
        {
            free_node(*ast);
            return PARSER_ERROR;
        }

        (*ast)->data.ast_and_or.right = other;
        com = *ast;

        tok = lexer_peek(input);
    }

    return PARSER_FOUND;
}
