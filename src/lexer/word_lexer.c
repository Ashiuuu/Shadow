#include "lexer.h"

struct word_lexer *new_word_lexer()
{
    struct word_lexer *ret = malloc(sizeof(struct word_lexer));
    if (ret == NULL)
    {
        fprintf("Malloc fail");
        abort();
    }

    ret->capacity = 10;
    ret->value = xmalloc(sizeof(char) * ret->capacity);
    ret->len = 0;
    ret->state = LEXER_CONT;

    return ret;
}

void reset_word_lexer(struct word_lexer *lexer)
{
    if (lexer->value != NULL)
        free(lexer->value);
    lexer->len = 0;
    lexer->state = LEXER_CONT;
}

enum lexer_state word_lexer_consume_char(struct word_lexer *lexer, char c)
{
    if (lexer->state == LEXER_ERROR)
        return LEXER_ERROR;


    if (lexer->input->next_char == ' ' || lexer->input->next_char == ';' || lexer->input->next_char == '\n') // end of word
    {
        lexer->state = LEXER_ACCEPT;
        lexer->capacity = lexer->len + 1;
        lexer->value = xrealloc(lexer->value, sizeof(char) * lexer->capacity);
        lexer->value[lexer->len] = '\0';
        return LEXER_ACCEPT;
    }

    if (is_alphanum(lexer->input->current_char))
    {
        // valid character
        if (lexer->len == lexer->capacity)
        {
            lexer->capacity *= 2;
            lexer->value = xrealloc(lexer->value, sizeof(char) * lexer->capacity);
        }
        lexer->value[lexer->len] = lexer->input->current_char;
        return LEXER_CONT;
    }

    // not a valid char
    lexer->state = LEXER_ERROR;
    return LEXER_ERROR;
}