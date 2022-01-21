#include "lexer.h"

int is_numeral(char c)
{
    return c >= '0' && c <= '9';
}

struct general_lexer *new_io_number_lexer()
{
    struct general_lexer *ret = xmalloc(sizeof(struct general_lexer));

    ret->type = IO_NUMBER_LEXER;
    ret->state = LEXER_CONT;
    ret->data.io_number_lexer.capacity = 10;
    ret->data.io_number_lexer.len = 0;
    ret->data.io_number_lexer.value =
        xmalloc(sizeof(char) * ret->data.io_number_lexer.capacity);

    return ret;
}

void free_io_number_lexer(struct general_lexer *lexer)
{
    if (lexer->type != IO_NUMBER_LEXER)
    {
        fprintf(stderr, "trying to free non word lexer\n");
        return;
    }

    if (lexer->data.io_number_lexer.value != NULL)
        free(lexer->data.io_number_lexer.value);

    free(lexer);
}

void reset_io_number_lexer(struct general_lexer *lexer)
{
    if (lexer->type != IO_NUMBER_LEXER)
    {
        fprintf(stderr, "trying to reset non word lexer\n");
        return;
    }

    if (lexer->data.io_number_lexer.value != NULL)
        free(lexer->data.io_number_lexer.value);

    lexer->data.io_number_lexer.capacity = 10;
    lexer->data.io_number_lexer.len = 0;
    lexer->state = LEXER_CONT;
    lexer->data.io_number_lexer.value =
        xmalloc(sizeof(char) * lexer->data.io_number_lexer.capacity);
}

enum lexer_state io_number_lexer_consume_char(struct general_lexer *lexer,
                                              struct INPUT *input)
{
    if (lexer->type != IO_NUMBER_LEXER)
    {
        fprintf(stderr, "trying to consume char for non word lexer\n");
        return LEXER_ERROR;
    }

    if (lexer->state == LEXER_ERROR)
        return LEXER_ERROR;

    if (!(input->current_char == '<' || input->current_char == '>')
        && !is_numeral(input->current_char))
    {
        // invalid char
        lexer->state = LEXER_ERROR;
        return LEXER_ERROR;
    }

    if (lexer->data.io_number_lexer.len == 0
        && (input->current_char == '<' || input->current_char == '>'))
    {
        // we have ended parsing but no number was found, so no token
        lexer->state = LEXER_ERROR;
        return LEXER_ERROR;
    }

    if (is_numeral(input->current_char))
    {
        // add num at value
        if (lexer->data.io_number_lexer.len
            == lexer->data.io_number_lexer.capacity)
        {
            lexer->data.io_number_lexer.capacity *= 2;
            lexer->data.io_number_lexer.value =
                xrealloc(lexer->data.io_number_lexer.value,
                         sizeof(char) * lexer->data.io_number_lexer.capacity);
        }
        lexer->data.io_number_lexer.value[lexer->data.io_number_lexer.len] =
            input->current_char;
        lexer->data.io_number_lexer.len++;
        return LEXER_CONT;
    }
    else
    {
        // only case missing, we have an ending char and non zero lenght, which
        // means we have a number, so accept
        lexer->state = LEXER_ACCEPT;
        lexer->data.io_number_lexer.capacity =
            lexer->data.io_number_lexer.len + 1;
        lexer->data.io_number_lexer.value =
            xrealloc(lexer->data.io_number_lexer.value,
                     sizeof(char) * lexer->data.io_number_lexer.capacity);
        lexer->data.io_number_lexer.value[lexer->data.io_number_lexer.len] =
            '\0';
        return LEXER_ACCEPT;
    }
}
