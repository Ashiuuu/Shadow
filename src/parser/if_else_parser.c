#include "parser.h"

//Grammar:
//   ELSE compound_list
// | ELIF compound_list THEN compound_list [else_clause]
enum parser_status parse_else_clause(struct ast_node **ast, struct lexer *input)
{
    struct token *tok = lexer_peek(input);
    *ast = new_if_node();

    if (tok->type == TOKEN_ELSE)
    {
        lexer_pop(input);
        struct ast_node *body = NULL;
        parse_compound_list(&body, input);
        (*ast)->data.ast_if.body_list = body;
        return PARSER_OK;
    }
    else if (tok->type == TOKEN_ELIF)
    {
        lexer_pop(input);
        struct ast_node *cond = NULL;
        struct ast_node *body = NULL;
        struct ast_node *elsif = NULL;

        parse_compound_list(&cond, input);
        (*ast)->data.ast_if.condition = cond;

        tok = lexer_peek(input);
        if (tok->type != TOKEN_THEN)
        {
            fprintf(stderr, "missing THEN token\n");
            return PARSER_ERROR;
        }
        lexer_pop(input);
        parse_compound_list(&body, input);
        (*ast)->data.ast_if.body_list = body;

        tok = lexer_peek(input);
        if (tok->type == TOKEN_ELIF || tok->type == TOKEN_ELSE)
        {
            parse_else_clause(&elsif, input);
            (*ast)->data.ast_if.elif = elsif;
            return PARSER_OK;
        }

        return PARSER_OK;
    }

    return PARSER_ERROR;
}

// Grammar:
// IF compound_list THEN compound_list [else_clause] FI
enum parser_status parse_rule_if(struct ast_node **ast, struct lexer *input)
{
    struct token *tok = lexer_peek(input);
    if (tok->type != TOKEN_IF)
    {
        fprintf(stderr, "expected IF\n");
        return PARSER_ERROR;
    }

    *ast = new_if_node();

    lexer_pop(input);
    struct ast_node *compound = NULL;
    parse_compound_list(&compound, input);
    (*ast)->data.ast_if.condition = compound;

    tok = lexer_peek(input);
    if (tok->type != TOKEN_THEN)
    {
        fprintf(stderr, "expected THEN\n");
        return PARSER_ERROR;
    }

    lexer_pop(input);
    compound = NULL;
    parse_compound_list(&compound, input);
    (*ast)->data.ast_if.body_list = compound;

    tok = lexer_peek(input);
    if (tok->type == TOKEN_ELIF || tok->type == TOKEN_ELSE)
    {
        struct ast_node *elsif = NULL;
        parse_else_clause(&elsif, input);
        (*ast)->data.ast_if.elif = elsif;
        tok = lexer_peek(input);
    }

    if (tok->type != TOKEN_FI)
    {
        fprintf(stderr, "expected FI\n");
        return PARSER_ERROR;
    }

    return PARSER_OK;
}