#include "parser.h"

// Grammar :
//   list '\n'
// | list EOF
// | '\n'
// | EOF
enum parser_status parse_input(struct ast_node_command *ast, struct lexer *input)
{
    // for now:
    //   simple_command '\n'
    // | simple_command EOF
    // | '\n'
    // | EOF

    struct token *token = lexer_peek(input);

    if (token->type == TOKEN_EOF || token->type == TOKEN_EOL)
    {
        lexer_pop(input);
        // execute command ?
        return PARSER_OK;   
    }

    if (token->type == TOKEN_WORDS)
    {
        return parser_simple_command(ast, input);
    }

    fprintf(stderr, "Unexpected token");
    return PARSER_ERROR;
}

// Grammar :
//   (prefix)+
// | (prefix)* (element)+
enum parser_status parser_simple_command(struct ast_node_command *ast, struct lexer *input)
{
    // for now simple command is just WORD+ ie 'ls /bin' or 'pwd'
    // for now, just create ast node, execute and exit
    size_t capacity = 10;
    char **args = xcalloc(capacity, sizeof(char *));

    size_t i = 0;
    struct token *token = lexer_peek(input);
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
    ast = new_command_node(args);
    exec_command_node(ast);
    return PARSER_OK;
}

// Grammar :
//   '{' compound_list '}'
// | '(' compound_list ')'
// | rule_for
// | rule_while
// | rule_until
// | rule_case
// | rule_if
enum parser_status parse_shell_command(struct lexer *input)
{
    // just if for now
    input = input;

    return PARSER_OK;
}

// Grammar :
// if compound_list  then compound_list [else_clause] fi
enum parser_status parse_if(struct lexer *input)
{
    input = input;

    return PARSER_OK;
}

// Grammar :
//   else compound_list
// | elif compound_list then compound_list [else_clause]
enum parser_status parse_else(struct lexer *input)
{
    input = input;

    return PARSER_OK;
}
