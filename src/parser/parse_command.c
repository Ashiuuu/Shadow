#include "parser.h"

// command grammar:
//   simple_command
// | shell_command
enum parser_status parse_command(struct ast_node **ast, struct lexer *input)
{
    struct token *tok = lexer_peek(input);

    if (tok->type == TOKEN_EOF || tok->type == TOKEN_EOL)
        return PARSER_ERROR;

    if (tok->type == TOKEN_WORDS || tok->type == TOKEN_IO_NUMBER
        || is_redirec_token(tok->type))
    {
        return parser_simple_command(ast, input);
    }

    struct ast_node *com = NULL;
    enum parser_status stat = parse_shell_command(&com, input);
    if (stat == PARSER_ERROR)
        return PARSER_ERROR;

    // now parse redirections
    *ast = new_redirec_list_node();
    (*ast)->data.ast_redirec_list.child = com;

    struct redirection *red = NULL;
    enum parser_status cont = parse_redirection(&red, input);
    while (cont == PARSER_OK)
    {
        push_redirec_list_node(*ast, red);
        cont = parse_redirection(&red, input);
    }

    return stat;
}

// Grammar :
//   (prefix)+
// | (prefix)* (element)+
// Basically, redirections and WORDS
// we put WORDS in a command node and redirections in a redirection list
// then put the command as child of the redirection list
enum parser_status parser_simple_command(struct ast_node **ast,
                                         struct lexer *input)
{
    struct token *tok = lexer_peek(input);
    *ast = new_redirec_list_node();

    size_t capacity = 5;
    size_t len = 0;
    char **args = xmalloc(sizeof(char *) * capacity);

    while (tok->type == TOKEN_IO_NUMBER || tok->type == TOKEN_WORDS
           || is_redirec_token(tok->type))
    {
        if (tok->type == TOKEN_IO_NUMBER || is_redirec_token(tok->type))
        {
            struct redirection *red = NULL;
            enum parser_status stat = parse_redirection(&red, input);
            if (stat == PARSER_ERROR)
            {
                for (size_t i = 0; i < len; ++i)
                    free(args[i]);
                free(args);
                free_node(*ast);
                return PARSER_ERROR;
            }

            push_redirec_list_node(
                *ast, red); // we push the redirection we got to the stack
        }
        else // we found a word, push it to the args
        {
            if (len == capacity)
            {
                capacity *= 2;
                args = xrealloc(args, sizeof(char *) * capacity);
            }
            args[len] = strdup(tok->value);
            len++;
        }

        tok = lexer_pop_ignore_keyword(input);
    }

    struct ast_node *c = NULL;

    if (len != 0)
    {
        capacity = len + 1;
        args = xrealloc(args, sizeof(char *) * capacity);
        args[len] = NULL;
        c = new_command_node(args);
    }

    (*ast)->data.ast_redirec_list.child = c;

    return PARSER_OK;
}

enum parser_status parse_shell_command(struct ast_node **ast,
                                       struct lexer *input)
{
    struct token *tok = lexer_peek(input);

    if (tok->type == TOKEN_IF)
    {
        return parse_rule_if(ast, input);
    }
    if (tok->type == TOKEN_WHILE)
    {
        return parse_rule_while(ast, input);
    }
    if (tok->type == TOKEN_UNTIL)
    {
        return parse_rule_until(ast, input);
    }

    // printf(stderr, "Unable to parse shell command\n");
    return PARSER_ERROR;
}