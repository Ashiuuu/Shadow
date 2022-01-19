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
    struct token *token = lexer_peek(input);

    if (token->type == TOKEN_EOF || token->type == TOKEN_EOL)
    {
        lexer_free(input);
        return PARSER_OK;
    }

    enum parser_status ret_status = parse_list(ast, input);

    if (ret_status != PARSER_OK)
    {
        fprintf(stderr, "Unexpected token\n");
        lexer_free(input);
        return PARSER_ERROR;
    }

    token = lexer_peek(input);

    if (token->type == TOKEN_EOF || token->type == TOKEN_EOL)
    {
        lexer_pop(input);
        lexer_free(input);
        return PARSER_OK;
    }

    fprintf(stderr, "Expected EOF or EOL token\n");
    lexer_free(input);
    return PARSER_ERROR;
}

// list grammar:
// and_or ((';'|'&') and_or)* [';'|'&']
// for now, and_or is pipelines separated by ';'
enum parser_status parse_list(struct ast_node **ast, struct lexer *input)
{
    *ast = new_list_node();

    struct ast_node *com = NULL;
    enum parser_status stat = parse_and_or(&com, input);
    if (stat == PARSER_ERROR)
    {
        // fprintf(stderr, "[FATAL] no command found in list??\n");
        free_node(*ast);
        return PARSER_ERROR;
    }

    list_node_push(*ast, com);
    struct token *tok = lexer_peek(input);
    if (tok->type == TOKEN_SEMICOL)
    {
        while (tok->type == TOKEN_SEMICOL || stat == PARSER_OK)
        {
            // stop redirection if started
            if (tok->type == TOKEN_SEMICOL)
                tok = lexer_pop(input);

            struct ast_node *new_com = NULL;
            stat = parse_and_or(&new_com, input);
            if (stat == PARSER_ERROR)
            {
                // list ends here
                /*fprintf(stderr, "[FATAL] no command found in list??
                (loop)\n"); free_node(*ast); return PARSER_ERROR;*/
                // return PARSER_OK;
                continue;
            }
            list_node_push(*ast, new_com);
            tok = lexer_peek(input);
        }
    }

    return PARSER_OK;
}

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

// Grammar :
// list: command (';' command)* [';']
enum parser_status parse_command_list(struct ast_node **ast,
                                      struct lexer *input)
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
enum parser_status parse_compound_list(struct ast_node **ast,
                                       struct lexer *input)
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
    while (tok->type == TOKEN_SEMICOL
           || tok->type == TOKEN_EOL) // ((';'|'\n') ('\n')* and_or)*
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
