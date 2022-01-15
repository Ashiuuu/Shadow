#include "parser.h"

// Grammar:
// While compound_list do_group
enum parser_status parse_rule_while(struct ast_node **ast, struct lexer *input)
{
    struct token *tok = lexer_peek(input);
    if (tok->type != TOKEN_WHILE)
    {
        fprintf(stderr, "expected while\n");
        return PARSER_ERROR;
    }

    lexer_pop(input);

    *ast = new_while_node();
    struct ast_node *comp = NULL;
    enum parser_status ret = parse_compound_list(&comp, input);
    if (ret == PARSER_ERROR)
    {
        free_node(*ast);
        return PARSER_ERROR;
    }
    (*ast)->data.ast_while.condition = comp;

    struct ast_node *body = NULL;
    ret = parse_do_group(&body, input);
    if (ret == PARSER_ERROR)
    {
        free_node(*ast);
        return PARSER_ERROR;
    }
    (*ast)->data.ast_while.body_list = body;

    return PARSER_OK;
}

enum parser_status parse_do_group(struct ast_node **ast, struct lexer *input)
{
    struct token *tok = lexer_peek(input);
    if (tok->type != TOKEN_DO)
    {
        fprintf(stderr, "expected do\n");
        return PARSER_ERROR;
    }

    lexer_pop(input);
    parse_compound_list(ast, input);

    tok = lexer_pop(input);
    if (tok->type == TOKEN_DONE)
    {
        fprintf(stderr, "expected done\n");
        return PARSER_ERROR;
    }
    return PARSER_OK;
}