#include "lexer.h"
#include "utils.h"

int is_alpha(char c)
{
    return ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A'));
}

int is_num(char c)
{
    return (c <= '9' && c >= '0');
}

int is_alphanum(char c)
{
    return (is_alpha(c) || is_num(c));
}

struct token *token_swap(struct lexer *lexer, struct token *new_token)
{
    if (lexer->current_token != NULL)
        token_free(lexer->current_token);
    lexer->current_token = new_token;

    return lexer->current_token;
}

void lexer_free(struct lexer *lexer)
{
    if (lexer->current_token != NULL)
        free(lexer->current_token);
    if (lexer->input != NULL)
        free_input(lexer->input);
    if (lexer->lexer_list != NULL)
    {
        for (size_t i = 0; i < lexer->list_len; ++i)
            general_lexer_free(lexer->lexer_list[i]);
        free(lexer->lexer_list);
    }
    free(lexer);
}
