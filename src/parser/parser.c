#include "parser.h"
#include "utils.h"

// Grammar :
//   list '\n'
// | list EOF
// | '\n'
// | EOF
enum parser_status parse_input(struct ast_node **ast, struct lexer *input)
{
    struct token *token = lexer_peek(input);

    if (token->type == TOKEN_EOF || token->type == TOKEN_EOL)
    {
        lexer_pop(input);
        return PARSER_OK;   
    }

    if (token->type == TOKEN_WORDS)
    {
        return parse_list(ast, input);
    }

    fprintf(stderr, "Unexpected token\n");
    return PARSER_ERROR;
}

// Grammar :
//   (prefix)+
// | (prefix)* (element)+
enum parser_status parser_simple_command(struct ast_node **ast, struct lexer *input)
{
    // for now simple command is just WORD+ ie 'ls /bin' or 'pwd'
    // for now, just create ast node, execute and exit
    struct token *token = lexer_peek(input);
    if (token->type != TOKEN_WORDS)
    {
        // we had no command
        return PARSER_ERROR;
    }

    size_t capacity = 10;
    char **args = xcalloc(capacity, sizeof(char *));

    size_t i = 0;
    while (token->type == TOKEN_WORDS)
    {
        if (i == capacity)
        {
            capacity *= 2;
            args = xrealloc(args, capacity);
        }
        args[i] = strdup(token->value);
        i++;
        token = lexer_pop(input);
    }
    // finished parsing words, now exec
    *ast = new_command_node(args);
    return PARSER_OK;
}

// Grammar :
// list: command (';' command)* [';']
enum parser_status parse_command_list(struct ast_node **ast, struct lexer *input)
{
    *ast = new_list_node();

    struct ast_node *new = NULL;
    enum parser_status stat = parser_simple_command(&new, input);
    // handle status error
    if (stat != 0)
    {
        fprintf(stderr, "error parsing command\n");
        return PARSER_ERROR;
    }

    list_node_push(*ast, new);

    struct token *token = lexer_peek(input);
    enum token_type last_token = TOKEN_WORDS;
    while (token->type == TOKEN_SEMICOL || token->type == TOKEN_WORDS)
    {
        if (token->type == TOKEN_SEMICOL && last_token == TOKEN_WORDS)
        {
            last_token = TOKEN_SEMICOL;
            token = lexer_pop(input);
        }
        else if (token->type == TOKEN_WORDS && last_token == TOKEN_SEMICOL)
        {
            struct ast_node *new_node = NULL;
            stat = parser_simple_command(&new_node, input);
            if (stat != 0)
            {
                fprintf(stderr, "error parsing command\n");
                return PARSER_ERROR;
            }
            list_node_push(*ast, new_node);
            last_token = TOKEN_WORDS;
            token = lexer_peek(input);
        }
        else
        {
            return PARSER_ERROR;
        }
    }
    return PARSER_OK;
}


// Grammar:
// ('\n')* and_or ((';'|'\n') ('\n')* and_or)* [(';'|'\n') ('\n')*]
// and_or = command for now
enum parser_status parse_compound_list(struct ast_node **ast, struct lexer *input)
{
    *ast = new_list_node();

    struct token *tok = lexer_peek(input);
    while (tok->type == TOKEN_EOL) // ('\n')*
        lexer_pop(input);

    // first and_or
    struct ast_node *com = NULL;
    parser_simple_command(&com, input);
    list_node_push(*ast, com);

    tok = lexer_peek(input);
    while (tok->type == TOKEN_SEMICOL || tok->type == TOKEN_EOL) // ((';'|'\n') ('\n')* and_or)*
    {
        tok = lexer_peek(input);

        if (tok->type != TOKEN_EOL && tok->type != TOKEN_SEMICOL)
            break;

        // we saw ; or \n, pop token
        tok = lexer_pop(input);
        while (tok->type == TOKEN_EOL)
            tok = lexer_pop(input);

        // we either have a and_or or we are over
        if (tok->type == TOKEN_WORDS) // we have a command
        {
            struct ast_node *new_com = NULL;
            parser_simple_command(&new_com, input);
            list_node_push(*ast, new_com);
        }
        else // compound list is over
        {
            return PARSER_OK;
        }
        tok = lexer_peek(input);
    }

    // we shouldn't get here
    return PARSER_ERROR;
}

enum parser_status parse_shell_command(struct ast_node **ast, struct lexer *input)
{
    struct token *tok = lexer_peek(input);

    if (tok->type == TOKEN_IF)
    {
        return parse_rule_if(ast, input);
    }

    // printf(stderr, "Unable to parse shell command\n");
    return PARSER_ERROR;
}

// command grammar:
//   simple_command
// | shell_command
enum parser_status parse_command(struct ast_node **ast, struct lexer *input)
{
    struct token *tok = lexer_peek(input);

    if (tok->type == TOKEN_WORDS)
    {
        return parser_simple_command(ast, input);
    }

    return parse_shell_command(ast, input);
}

// list grammar:
// command (';' command)* [';']
enum parser_status parse_list(struct ast_node **ast, struct lexer *input)
{
    *ast = new_list_node();

    struct ast_node *com = NULL;
    enum parser_status stat = parse_command(&com, input);
    if (stat == PARSER_ERROR)
    {
        fprintf(stderr, "error\n");
        return PARSER_ERROR;
    }

    list_node_push(*ast, com);
    struct token *tok = lexer_peek(input);
    while (tok->type == TOKEN_SEMICOL || stat == PARSER_OK)
    {
        if (tok->type == TOKEN_SEMICOL)
            lexer_pop(input);
       
        struct ast_node *new_com = NULL;
        stat = parse_command(&new_com, input);
        if (stat == PARSER_OK)
        {
            list_node_push(*ast, new_com);
        }
        tok = lexer_peek(input);
    }

    return PARSER_OK;
}