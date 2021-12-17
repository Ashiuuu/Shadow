#include "lexer.h"

struct keyword_lexer *new_keyword_lexer(const char *word)
{
    struct keyword_lexer *ret = malloc(sizeof(struct keyword_lexer));
    if (ret == NULL)
    {
        fprintf("Malloc fail");
        abort();
    }

    ret->keyword = word;
    ret->word_len = strlen(word);
    ret->pos = 0;
    ret->state = LEXER_CONT;

    return ret;
}

void reset_keyword_lexer(struct keyword_lexer *lexer)
{
    ret->pos = 0;
    ret->state = LEXER_CONT;
}

enum lexer_state keyword_lexer_consume_char(struct keyword_lexer *lexer, char c)
{
    if (lexer->state == LEXER_ERROR)
    {
        // trying to consume characters when we encountered an error
        return LEXER_ERROR;
    }

    if (lexer->pos >= lexer->word_len) // we already went through the last char
    {
        if (c == ' ' || c == ';') // punctuation
        {
            lexer->state = LEXER_ACCEPT;
            return LEXER_ACCEPT;
        }
        lexer->state = LEXER_ERROR;
        return LEXER_ERROR;
    }

    if (lexer->word[lexer->pos] == c)
    {
        // valid character, simply continue
        lexer->pos++;
        return LEXER_CONT;
    }
    // current character is not good
    lexer->state = LEXER_ERROR;
    return LEXER_ERROR;
}