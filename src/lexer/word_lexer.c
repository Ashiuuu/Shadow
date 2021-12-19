#include "lexer.h"

struct word_lexer *new_word_lexer()
{
    struct word_lexer *ret = xmalloc(sizeof(struct word_lexer));

    ret->capacity = 10;
    ret->value = xmalloc(sizeof(char) * ret->capacity);
    ret->len = 0;
    ret->state = LEXER_CONT;

    return ret;
}

void free_word_lexer(struct word_lexer *lexer)
{
    if (lexer->value != NULL)
        free(lexer->value);

    free(lexer);
}

void reset_word_lexer(struct word_lexer *lexer)
{
    if (lexer->value != NULL)
        free(lexer->value);
    lexer->capacity = 10;
    lexer->value = xmalloc(sizeof(char) * lexer->capacity);
    lexer->len = 0;
    lexer->state = LEXER_CONT;
}

enum lexer_state word_lexer_consume_char(struct word_lexer *lexer, struct INPUT *input)
{
    if (lexer->state == LEXER_ERROR)
        return LEXER_ERROR;

    if (is_alphanum(input->current_char))
    {
        // valid character
        if (lexer->len == lexer->capacity)
        {
            lexer->capacity *= 2;
            lexer->value = xrealloc(lexer->value, sizeof(char) * lexer->capacity);
        }
        lexer->value[lexer->len] = input->current_char;
        lexer->len++;
        return LEXER_CONT;
    }

    if (input->current_char == ' ' || input->current_char == ';' || input->current_char == '\n' || input->current_char == EOF) // end of word
    {
        lexer->state = LEXER_ACCEPT;
        lexer->capacity = lexer->len + 1;
        lexer->value = xrealloc(lexer->value, sizeof(char) * lexer->capacity);
        lexer->value[lexer->len] = '\0';
        return LEXER_ACCEPT;
    }

    // not a valid char
    lexer->state = LEXER_ERROR;
    return LEXER_ERROR;
}