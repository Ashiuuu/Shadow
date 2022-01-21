#include "parser.h"

enum parser_status parse_rule_until(struct ast_node **ast, struct lexer *input)
{
    struct token *tok = lexer_peek(input);
    if (tok->type != TOKEN_UNTIL)
    {
        fprintf(stderr, "expected until\n");
        return PARSER_ERROR;
    }

    lexer_pop(input);

    *ast = new_until_node();
    struct ast_node *comp = NULL;
    enum parser_status ret = parse_compound_list(&comp, input);
    if (ret == PARSER_ERROR)
    {
        free_node(*ast);
        return PARSER_ERROR;
    }
    (*ast)->data.ast_until.condition = comp;

    struct ast_node *body = NULL;
    ret = parse_do_group(&body, input);
    if (ret == PARSER_ERROR)
    {
        free_node(*ast);
        return PARSER_ERROR;
    }
    (*ast)->data.ast_until.body_list = body;

    return PARSER_OK;
}
