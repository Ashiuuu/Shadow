#include "lexer.h"

struct keyword_lexer *new_keyword_lexer(const char *word)
{
    struct keyword_lexer *ret = xmalloc(sizeof(struct keyword_lexer));

    ret->keyword = word;
    ret->word_len = strlen(word);
    ret->pos = 0;
    ret->state = LEXER_CONT;

    return ret;
}

void reset_keyword_lexer(struct keyword_lexer *lexer)
{
    lexer->pos = 0;
    lexer->state = LEXER_CONT;
}

enum lexer_state keyword_lexer_consume_char(struct keyword_lexer *lexer, struct INPUT *input)
{
    if (lexer->state == LEXER_ERROR)
    {
        // trying to consume characters when we encountered an error
        return LEXER_ERROR;
    }

    if (lexer->pos >= lexer->word_len) // we already went through the last char
    {
        if (input->current_char == ' ' || input->current_char == ';') // punctuation
        {
            lexer->state = LEXER_ACCEPT;
            return LEXER_ACCEPT;
        }
        lexer->state = LEXER_ERROR;
        return LEXER_ERROR;
    }

    if (lexer->keyword[lexer->pos] == input->current_char)
    {
        // valid character, simply continue
        lexer->pos++;
        return LEXER_CONT;
    }
    // current character is not good
    lexer->state = LEXER_ERROR;
    return LEXER_ERROR;
}