#include "lexer.h"

struct general_lexer *new_sing_quote_lexer()
{
    struct general_lexer *ret = xmalloc(sizeof(struct general_lexer));

    ret->type = SING_QUOTE_LEXER;
    ret->state = LEXER_CONT;
    ret->data.sing_quote_lexer.capacity = 10;
    ret->data.sing_quote_lexer.len = 0;
    ret->data.sing_quote_lexer.value =
        xmalloc(sizeof(char) * ret->data.sing_quote_lexer.capacity);
    ret->data.sing_quote_lexer.quote_flag = 0;

    return ret;
}

void free_sing_quote_lexer(struct general_lexer *lexer)
{
    if (lexer->type != SING_QUOTE_LEXER)
    {
        fprintf(stderr, "trying to free non single quote lexer\n");
        return;
    }

    if (lexer->data.sing_quote_lexer.value != NULL)
        free(lexer->data.sing_quote_lexer.value);

    free(lexer);
}

void reset_sing_quote_lexer(struct general_lexer *lexer)
{
    if (lexer->type != SING_QUOTE_LEXER)
    {
        fprintf(stderr, "trying to reset non single quote lexer\n");
        return;
    }

    if (lexer->data.sing_quote_lexer.value != NULL)
        free(lexer->data.sing_quote_lexer.value);

    lexer->data.sing_quote_lexer.capacity = 10;
    lexer->data.sing_quote_lexer.len = 0;
    lexer->state = LEXER_CONT;
    lexer->data.sing_quote_lexer.value =
        xmalloc(sizeof(char) * lexer->data.sing_quote_lexer.capacity);
}

enum lexer_state sing_quote_lexer_consume_char(struct general_lexer *lexer,
                                               struct INPUT *input)
{
    if (lexer->type != SING_QUOTE_LEXER)
    {
        fprintf(stderr, "trying to consume char for non single quote lexer\n");
        return LEXER_ERROR;
    }

    if (lexer->state == LEXER_ERROR)
        return LEXER_ERROR;

    if (lexer->data.sing_quote_lexer.len == 0
        && input->current_char == '\'') // if it is the first char and a '
    {
        // start getting chars
        lexer->data.sing_quote_lexer.quote_flag = 1; // set flag
        return LEXER_CONT;
    }
    else if (lexer->data.sing_quote_lexer.quote_flag != 0
             && input->current_char == '\'') // flag was set (we encountered a '
                                             // before) and we see another one
    {
        // end parsing
        lexer->state = LEXER_ACCEPT;
        lexer->data.sing_quote_lexer.quote_flag =
            0; // shouldn't be necessary, just in case
        lexer->data.sing_quote_lexer.capacity =
            lexer->data.sing_quote_lexer.len + 1; // space for terminating \0
        lexer->data.sing_quote_lexer.value =
            xrealloc(lexer->data.sing_quote_lexer.value,
                     sizeof(char) * lexer->data.sing_quote_lexer.capacity);
        lexer->data.sing_quote_lexer.value[lexer->data.sing_quote_lexer.len] =
            '\0';
        // in lexing like words, we stop when we encounter for example a ;, but
        // we don't want to consume the ; here, the ' signals the end, but we DO
        // want to consume it
        pop_char(input);
        return LEXER_ACCEPT;
    }
    else if (lexer->data.sing_quote_lexer.quote_flag
             != 0) // quote flag is set but we are not at the end
    {
        // continue getting chars
        if (lexer->data.sing_quote_lexer.len
            == lexer->data.sing_quote_lexer.capacity)
        {
            // resize
            lexer->data.sing_quote_lexer.capacity *= 2;
            lexer->data.sing_quote_lexer.value =
                xrealloc(lexer->data.sing_quote_lexer.value,
                         sizeof(char) * lexer->data.sing_quote_lexer.capacity);
        }
        lexer->data.sing_quote_lexer.value[lexer->data.sing_quote_lexer.len] =
            input->current_char;
        lexer->data.sing_quote_lexer.len++;
        return LEXER_CONT;
    }

    // flag is unset and we are not at the beggining, ie ???
    lexer->state = LEXER_ERROR;
    return LEXER_ERROR;
}