#include "parser.h"

#include "utils.h"

int is_redirec_token(enum token_type type)
{
    return type == TOKEN_FRED_IN || type == TOKEN_FRED_OUT
        || type == TOKEN_FDRED_IN || type == TOKEN_FDRED_OUT
        || type == TOKEN_FRED_APP || type == TOKEN_BIRED
        || type == TOKEN_FRED_FORCE;
}

// Grammar :
//   list '\n'
// | list EOF
// | '\n'
// | EOF
enum parser_status parse_input(struct ast_node **ast, struct lexer *input)
{
    struct token *tok = lexer_peek(input);
    if (tok->type == TOKEN_ERROR)
        return PARSER_ERROR;

    if (tok->type == TOKEN_EOF || tok->type == TOKEN_EOL)
    {
        lexer_free(input);
        return PARSER_OK;
    }

    enum parser_status stat = parse_list(ast, input);
    if (stat != PARSER_FOUND)
    {
        fprintf(stderr, "Unexpected token\n");
        lexer_free(input);
        return PARSER_ERROR;
    }

    tok = lexer_peek(input);

    if (tok->type == TOKEN_EOF || tok->type == TOKEN_EOL)
    {
        lexer_free(input);
        return PARSER_FOUND;
    }

    fprintf(stderr, "Expected EOF or EOL token\n");
    lexer_free(input);
    return PARSER_ERROR;
}

// list grammar:
// and_or ((';'|'&') and_or)* [';'|'&']
enum parser_status parse_list(struct ast_node **ast, struct lexer *input)
{
    struct ast_node *com = NULL;
    enum parser_status stat = parse_and_or(&com, input);
    if (stat != PARSER_FOUND)
        return stat;

    *ast = new_list_node();
    list_node_push(*ast, com);

    struct token *tok = lexer_peek(input);
    if (tok->type == TOKEN_ERROR)
    {
        free_node(*ast);
        return PARSER_ERROR;
    }

    while (tok->type == TOKEN_SEMICOL)
    {
        lexer_pop(input);

        struct ast_node *com = NULL;
        stat = parse_and_or(&com, input);
        if (stat == PARSER_ERROR)
        {
            free_node(*ast);
            return PARSER_ERROR;
        }
        if (stat == PARSER_OK)
            break;

        list_node_push(*ast, com);
        tok = lexer_peek(input);
    }

    return PARSER_FOUND;
}

// Grammar:
// ('\n')* and_or ((';'|'\n') ('\n')* and_or)* [(';'|'\n') ('\n')*]
enum parser_status parse_compound_list(struct ast_node **ast,
                                       struct lexer *input)
{
    struct token *tok = lexer_peek(input);
    if (tok->type == TOKEN_ERROR)
        return PARSER_ERROR;
    while (tok->type == TOKEN_EOL) // ('\n')*
        tok = lexer_pop(input);

    *ast = new_list_node();

    // first and_or
    struct ast_node *com = NULL;
    enum parser_status stat = parser_simple_command(&com, input);
    if (stat != PARSER_FOUND) // either error or didn'd anything
    {
        free_node(*ast);
        return stat;
    }
    list_node_push(*ast, com); // we found something, add to list

    tok = lexer_peek(input);
    if (tok->type == TOKEN_ERROR)
        return PARSER_ERROR;

    while (tok->type == TOKEN_SEMICOL
           || tok->type == TOKEN_EOL) // ((';'|'\n') ('\n')* and_or)*
    {
        // we saw ; or \n, pop token
        tok = lexer_pop(input);
        while (tok->type == TOKEN_EOL)
            tok = lexer_pop(input);

        // we either have a and_or or we are over
        struct ast_node *com = NULL;
        stat = parse_and_or(&com, input);
        if (stat == PARSER_ERROR)
        {
            free_node(*ast);
            return PARSER_ERROR;
        }
        if (stat == PARSER_OK) // no and_or
            continue; // we could have other ; or \n

        // PARSER_FOUND
        list_node_push(*ast, com);

        tok = lexer_peek(input);
    }

    // we found something
    return PARSER_FOUND;
}
