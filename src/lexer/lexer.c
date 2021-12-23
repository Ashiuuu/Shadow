#include "lexer.h"

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

struct lexer *lexer_new(struct INPUT *input_stream)
{
    struct lexer *ret = malloc(sizeof(struct lexer));
    if (ret == NULL)
    {
        fprintf(stderr, "Unable to create lexer");
        abort();
    }

    ret->input = input_stream;
    ret->current_token = NULL;
    ret->word_lexer = new_word_lexer();

    return ret;
}

void lexer_free(struct lexer *lexer)
{
    if (lexer->current_token != NULL)
        free(lexer->current_token);
    if (lexer->input != NULL)
        free_input(lexer->input);
    free(lexer);
}

struct token *token_swap(struct lexer *lexer, struct token *new_token)
{
    if (lexer->current_token != NULL)
        free(lexer->current_token);
    lexer->current_token = new_token;

    return lexer->current_token;
}

struct token *lexer_peek(struct lexer *lexer)
{
    if (lexer->current_token == NULL)
        read_until_new_token(lexer);
    return lexer->current_token;
}

struct token *lexer_pop(struct lexer *lexer)
{
    return read_until_new_token(lexer);
}

struct token *read_until_new_token(struct lexer *lexer)
{
    if (lexer->input->current_char == EOF)
    {
        // new EOF token
        return token_swap(lexer, token_new(TOKEN_EOF));
    }

    while (lexer->input->current_char == ' ' || lexer->input->current_char == '\t')
        pop_char(lexer->input);

    while (lexer->word_lexer->state == LEXER_CONT)
    {
        enum lexer_state state = word_lexer_consume_char(lexer->word_lexer, lexer->input);
        if (state == LEXER_ERROR)
        {
            fprintf(stderr, "unexpected char %c\n", lexer->input->current_char);
            lexer->current_token = token_new(TOKEN_ERROR);
            return lexer->current_token;
        }
        pop_char(lexer->input);
    }
    token_swap(lexer, token_new_word(lexer->word_lexer->value));
    reset_word_lexer(lexer->word_lexer);
    return lexer->current_token;
}