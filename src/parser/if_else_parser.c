#include "parser.h"

// Grammar:
//   ELSE compound_list
// | ELIF compound_list THEN compound_list [else_clause]
enum parser_status parse_else_clause(struct ast_node **ast, struct lexer *input)
{
    struct token *tok = lexer_peek(input);
    if (tok->type == TOKEN_ERROR)
        return TOKEN_ERROR;

    *ast = new_if_node();

    if (tok->type == TOKEN_ELSE)
    {
        lexer_pop(input);
        struct ast_node *body = NULL;
        enum parser_status stat = parse_compound_list(&body, input);
        if (stat != PARSER_FOUND)
            goto error;
        
        (*ast)->data.ast_if.body_list = body;
        return PARSER_FOUND;
    }
    else if (tok->type == TOKEN_ELIF)
    {
        lexer_pop(input);
        struct ast_node *cond = NULL;
        struct ast_node *body = NULL;
        struct ast_node *elsif = NULL;

        enum parser_status stat = parse_compound_list(&cond, input);
        if (stat != PARSER_FOUND)
            goto error;

        (*ast)->data.ast_if.condition = cond;

        tok = lexer_peek(input);
        if (tok->type == TOKEN_ERROR)
            goto error;
        if (tok->type != TOKEN_THEN)
        {
            fprintf(stderr, "missing THEN token\n");
            goto error;
        }

        lexer_pop(input);
        stat = parse_compound_list(&body, input);
        if (stat != PARSER_FOUND)
            goto error;

        (*ast)->data.ast_if.body_list = body;

        tok = lexer_peek(input);
        if (tok->type == TOKEN_ERROR)
            goto error;

        if (tok->type == TOKEN_ELIF || tok->type == TOKEN_ELSE)
        {
            stat = parse_else_clause(&elsif, input);
            if (stat != PARSER_FOUND)
                goto error;
            (*ast)->data.ast_if.elif = elsif;
            return PARSER_FOUND;
        }

        return PARSER_FOUND;
    }

error:
    free_node(*ast);
    return PARSER_ERROR;
}

// Grammar:
// IF compound_list THEN compound_list [else_clause] FI
enum parser_status parse_rule_if(struct ast_node **ast, struct lexer *input)
{
    struct token *tok = lexer_peek(input);
    if (tok->type != TOKEN_IF)
    { // shouldn't happen, safeguard
        fprintf(stderr, "[FATAL] expected IF\n");
        return PARSER_ERROR;
    }

    tok = lexer_pop(input);
    if (tok->type == TOKEN_ERROR)
        return PARSER_ERROR;

    *ast = new_if_node();

    struct ast_node *compound = NULL;
    enum parser_status stat = parse_compound_list(&compound, input);
    if (stat != PARSER_FOUND)
        goto error;

    (*ast)->data.ast_if.condition = compound;

    tok = lexer_peek(input);
    if (tok->type == TOKEN_ERROR)
        goto error;
    if (tok->type != TOKEN_THEN)
    {
        fprintf(stderr, "expected THEN\n");
        goto error;
    }

    lexer_pop(input);
    compound = NULL;
    stat = parse_compound_list(&compound, input);
    if (stat != PARSER_FOUND)
        goto error;
    (*ast)->data.ast_if.body_list = compound;

    tok = lexer_peek(input);
    if (tok->type == TOKEN_ERROR)
        goto error;
    if (tok->type == TOKEN_ELIF || tok->type == TOKEN_ELSE)
    {
        struct ast_node *elsif = NULL;
        stat = parse_else_clause(&elsif, input);
        if (stat != PARSER_FOUND)
            goto error;
        (*ast)->data.ast_if.elif = elsif;
        tok = lexer_peek(input);
        if (tok->type == TOKEN_ERROR)
            goto error;
    }

    if (tok->type != TOKEN_FI)
        goto error;
    lexer_pop(input);

    return PARSER_FOUND;
error:
    free_node(*ast);
    return PARSER_ERROR;
}