#include "lexer.h"

struct general_lexer *new_keyword_lexer(const char *word, enum token_type type)
{
    struct general_lexer *ret = xmalloc(sizeof(struct general_lexer));

    ret->type = KEYWORD_LEXER;
    ret->state = LEXER_CONT;
    ret->data.keyword_lexer.keyword = word;
    ret->data.keyword_lexer.output_token = type;
    ret->data.keyword_lexer.pos = 0;
    ret->data.keyword_lexer.word_len = strlen(word);

    return ret;
}

void reset_keyword_lexer(struct general_lexer *lexer)
{
    if (lexer->type != KEYWORD_LEXER)
    {
        fprintf(stderr, "trying to reset non keyword lexer\n");
        return;
    }
    lexer->state = LEXER_CONT;
    lexer->data.keyword_lexer.pos = 0;
}

enum lexer_state keyword_lexer_consume_char(struct general_lexer *lexer,
                                            struct INPUT *input)
{
    if (lexer->type != KEYWORD_LEXER)
    {
        fprintf(stderr, "trying to consume char for non keyword lexer\n");
        return LEXER_ERROR;
    }

    if (lexer->state == LEXER_ERROR)
    {
        // trying to consume characters when we encountered an error
        return LEXER_ERROR;
    }

    if (lexer->data.keyword_lexer.pos
        >= lexer->data.keyword_lexer
               .word_len) // we already went through the last char
    {
        if (input->current_char == ' ' || input->current_char == ';'
            || input->current_char == EOF || (input->current_char == '\\' && input->next_char == 'n')) // punctuation
        {
            lexer->state = LEXER_ACCEPT;
            return LEXER_ACCEPT;
        }
        lexer->state = LEXER_ERROR;
        return LEXER_ERROR;
    }

    if (lexer->data.keyword_lexer.keyword[lexer->data.keyword_lexer.pos]
        == input->current_char)
    {
        // valid character, simply continue
        lexer->data.keyword_lexer.pos++;
        return LEXER_CONT;
    }
    // current character is not good
    lexer->state = LEXER_ERROR;
    return LEXER_ERROR;
}
