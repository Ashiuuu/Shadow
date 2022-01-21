#include "lexer.h"

struct general_lexer *new_double_quote_lexer()
{
    struct general_lexer *ret = xmalloc(sizeof(struct general_lexer));

    ret->type = DOUBLE_QUOTE_LEXER;
    ret->state = LEXER_CONT;
    ret->data.double_quote_lexer.capacity = 10;
    ret->data.double_quote_lexer.len = 0;
    ret->data.double_quote_lexer.value =
        xmalloc(sizeof(char) * ret->data.double_quote_lexer.capacity);
    ret->data.double_quote_lexer.quote_flag = 0;

    return ret;
}

void free_double_quote_lexer(struct general_lexer *lexer)
{
    if (lexer->type != DOUBLE_QUOTE_LEXER)
    {
        fprintf(stderr, "trying to free non double quote lexer\n");
        return;
    }

    if (lexer->data.double_quote_lexer.value != NULL)
        free(lexer->data.double_quote_lexer.value);

    free(lexer);
}

void reset_double_quote_lexer(struct general_lexer *lexer)
{
    if (lexer->type != DOUBLE_QUOTE_LEXER)
    {
        fprintf(stderr, "trying to reset non double quote lexer\n");
        return;
    }

    if (lexer->data.double_quote_lexer.value != NULL)
        free(lexer->data.double_quote_lexer.value);

    lexer->data.double_quote_lexer.capacity = 10;
    lexer->data.double_quote_lexer.len = 0;
    lexer->state = LEXER_CONT;
    lexer->data.double_quote_lexer.value =
        xmalloc(sizeof(char) * lexer->data.double_quote_lexer.capacity);
}

enum lexer_state double_quote_lexer_consume_char(struct general_lexer *lexer,
                                                 struct INPUT *input)
{
    if (lexer->type != DOUBLE_QUOTE_LEXER)
    {
        fprintf(stderr, "trying to consume char for non double quote lexer\n");
        return LEXER_ERROR;
    }

    if (lexer->state == LEXER_ERROR)
        return LEXER_ERROR;

    if (input->current_char == EOF)
    {
        lexer->state = LEXER_ERROR;
        return LEXER_ERROR;
    }

    if (lexer->data.double_quote_lexer.len == 0
        && input->current_char == '"') // if it is the first char and a "
    {
        // start getting chars
        lexer->data.double_quote_lexer.quote_flag = 1; // set flag
        return LEXER_CONT;
    }
    else if (lexer->data.double_quote_lexer.quote_flag != 0
             && input->current_char == '"') // flag was set (we encountered a '
                                            // before) and we see another one
    {
        // end parsing
        lexer->state = LEXER_ACCEPT;
        lexer->data.double_quote_lexer.quote_flag =
            0; // shouldn't be necessary, just in case
        lexer->data.double_quote_lexer.capacity =
            lexer->data.double_quote_lexer.len + 1; // space for terminating \0
        lexer->data.double_quote_lexer.value =
            xrealloc(lexer->data.double_quote_lexer.value,
                     sizeof(char) * lexer->data.double_quote_lexer.capacity);
        lexer->data.double_quote_lexer
            .value[lexer->data.double_quote_lexer.len] = '\0';
        // in lexing like words, we stop when we encounter for example a ;, but
        // we don't want to consume the ; here, the ' signals the end, but we DO
        // want to consume it
        pop_char(input);
        return LEXER_ACCEPT;
    }
    else if (lexer->data.double_quote_lexer.quote_flag
             != 0) // quote flag is set but we are not at the end
    {
        // continue getting chars
        if (lexer->data.double_quote_lexer.len
            == lexer->data.double_quote_lexer.capacity)
        {
            // resize
            lexer->data.double_quote_lexer.capacity *= 2;
            lexer->data.double_quote_lexer.value = xrealloc(
                lexer->data.double_quote_lexer.value,
                sizeof(char) * lexer->data.double_quote_lexer.capacity);
        }
        lexer->data.double_quote_lexer
            .value[lexer->data.double_quote_lexer.len] = input->current_char;
        lexer->data.double_quote_lexer.len++;
        return LEXER_CONT;
    }

    // flag is unset and we are not at the beggining, ie ???
    lexer->state = LEXER_ERROR;
    return LEXER_ERROR;
}
