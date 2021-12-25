#include "parser.h"

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
        printf("wait for it\n");
        return parse_command_list(ast, input);
    }

    fprintf(stderr, "Unexpected token");
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
// command
// ;
//   - finito
//   - command
//     - finito
//     - ;
//       - finito
//       - command
//         - ...
enum parser_status parse_command_list(struct ast_node **ast, struct lexer *input)
{
    printf("parsing list");
    *ast = new_list_node();

    struct ast_node *new = NULL;
    enum parser_status stat = parser_simple_command(&new, input);
    // handle status error
    if (stat != 0)
    {
        fprintf(stderr, "error parsing command");
        return PARSER_ERROR;
    }

    list_node_push(*ast, new);

    struct token *token = lexer_peek(input);
    enum token_type last_token = TOKEN_WORDS;
    while (token->type == TOKEN_SEMICOL || token->type == TOKEN_WORDS)
    {
        if (token->type == TOKEN_SEMICOL && last_token == TOKEN_WORDS)
        {
            lexer_pop(input);
        }
        else if (token->type == TOKEN_WORDS && last_token == TOKEN_SEMICOL)
        {
            struct ast_node *new_node = NULL;
            stat = parser_simple_command(&new_node, input);
            if (stat != 0)
            {
                fprintf(stderr, "error parsing command");
                return PARSER_ERROR;
            }
            list_node_push(*ast, new_node);
        }
        else
        {
            return PARSER_ERROR;
        }
    }
    return PARSER_OK;
}