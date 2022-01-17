#include "parser.h"

// Grammar
// ['!'] command ('|' ('\n')* command)*
enum parser_status parse_pipeline(struct ast_node **ast, struct lexer *input)
{
    struct token *tok = lexer_peek(input);

    int negated = 0;

    if (tok->type == TOKEN_PIPE_NEG)
    {
        negated = 1;
        tok = lexer_pop(input);
    }

    struct ast_node *com = NULL;
    enum parser_status com_stat = parse_command(&com, input);
    if (com_stat == PARSER_ERROR)
        return PARSER_ERROR;

    tok = lexer_peek(input);

    if (tok->type == TOKEN_PIPE)
    {
        // pipe
        lexer_pop(input);
        struct ast_node *pipe = new_pipe_node();
        pipe->data.ast_pipe.negated = negated;
        pipe->data.ast_pipe.left = com;
        *ast = pipe;
        enum token_type last_type = TOKEN_PIPE;

        while (last_type == TOKEN_PIPE)
        {
            tok = lexer_peek(input);
            while (tok->type == TOKEN_EOL)
                tok = lexer_pop(input);

            struct ast_node *right_com = NULL;
            enum parser_status right_stat = parse_command(&right_com, input);
            if (right_stat == PARSER_ERROR)
            {
                fprintf(stderr, "expected command at left of pipe\n");
                free_node(*ast);
                return PARSER_ERROR;
            }

            tok = lexer_pop(input);
            last_type = tok->type;

            if (tok->type == TOKEN_PIPE) // we have more than one pipe
            {
                struct ast_node *temp = new_pipe_node();
                pipe->data.ast_pipe.right = temp;
                pipe = temp;
            }
            else
            {
                pipe->data.ast_pipe.right = right_com;
            }
        }
    }
    else
    {
        // there was no pipe, just return the command
        *ast = com;
    }
    return PARSER_OK;
}