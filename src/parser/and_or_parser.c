#include "parser.h"

// Grammar:
// pipeline (('&&'|'||') ('\n')* pipeline)*
enum parser_status parse_and_or(struct ast_node **ast, struct lexer *input)
{
    struct token *tok = lexer_peek(input);
    
    struct ast_node *com = NULL;
    enum parser_status stat = parse_pipeline(&com, input);
    if (stat == PARSER_ERROR)
        return PARSER_ERROR;

    tok = lexer_peek(input);
    if (tok->type == TOKEN_AND || tok->type == TOKEN_OR)
    {
        while (tok->type == TOKEN_AND || tok->type == TOKEN_OR)
        {
            *ast = new_and_or_node(tok->type);
            (*ast)->data.ast_and_or.left = com;

            tok = lexer_pop(input);

            while (tok->type == TOKEN_EOL)
                tok = lexer_pop(input);

            struct ast_node *new_com = NULL;
            stat = parse_pipeline(&new_com, input);
            if (stat == PARSER_ERROR)
                return PARSER_ERROR;

            (*ast)->data.ast_and_or.right = new_com;
            com = *ast;

            tok = lexer_pop(input);
        }
    }
    else
    {
        *ast = com;
    }

    return PARSER_OK;
}