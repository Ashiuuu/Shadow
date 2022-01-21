#include "lexer.h"

int is_accepted_char(struct INPUT *input)
{
    char c = input->current_char;
    // char n = input->next_char;
    return is_alphanum(c) || c == '-' || c == '.' || c == '/' || c == ',';
}

struct general_lexer *new_word_lexer()
{
    struct general_lexer *ret = xmalloc(sizeof(struct general_lexer));

    ret->type = WORD_LEXER;
    ret->state = LEXER_CONT;
    ret->data.word_lexer.capacity = 10;
    ret->data.word_lexer.len = 0;
    ret->data.word_lexer.value =
        xmalloc(sizeof(char) * ret->data.word_lexer.capacity);

    return ret;
}

void free_word_lexer(struct general_lexer *lexer)
{
    if (lexer->type != WORD_LEXER)
    {
        fprintf(stderr, "trying to free non word lexer\n");
        return;
    }

    if (lexer->data.word_lexer.value != NULL)
        free(lexer->data.word_lexer.value);

    free(lexer);
}

void reset_word_lexer(struct general_lexer *lexer)
{
    if (lexer->type != WORD_LEXER)
    {
        fprintf(stderr, "trying to reset non word lexer\n");
        return;
    }

    if (lexer->data.word_lexer.value != NULL)
        free(lexer->data.word_lexer.value);

    lexer->data.word_lexer.capacity = 10;
    lexer->data.word_lexer.len = 0;
    lexer->state = LEXER_CONT;
    lexer->data.word_lexer.value =
        xmalloc(sizeof(char) * lexer->data.word_lexer.capacity);
}

enum lexer_state word_lexer_consume_char(struct general_lexer *lexer,
                                         struct INPUT *input)
{
    if (lexer->type != WORD_LEXER)
    {
        fprintf(stderr, "trying to consume char for non word lexer\n");
        return LEXER_ERROR;
    }

    if (lexer->state == LEXER_ERROR)
        return LEXER_ERROR;

    int accepted = is_accepted_char(input);

    if (input->current_char == '\\')
    {
        pop_char(input);
        switch (input->current_char)
        {
        case '\'':
            accepted = 1;
            break;
        }
    }

    if (accepted)
    {
        // valid character
        if (lexer->data.word_lexer.len == lexer->data.word_lexer.capacity)
        {
            lexer->data.word_lexer.capacity *= 2;
            lexer->data.word_lexer.value =
                xrealloc(lexer->data.word_lexer.value,
                         sizeof(char) * lexer->data.word_lexer.capacity);
        }
        lexer->data.word_lexer.value[lexer->data.word_lexer.len] =
            input->current_char;
        lexer->data.word_lexer.len++;
        return LEXER_CONT;
    }

    if (input->current_char == ' ' || input->current_char == ';'
        || input->current_char == '\n'
        || input->current_char == EOF) // end of word
    {
        lexer->state = LEXER_ACCEPT;
        lexer->data.word_lexer.capacity = lexer->data.word_lexer.len + 1;
        lexer->data.word_lexer.value =
            xrealloc(lexer->data.word_lexer.value,
                     sizeof(char) * lexer->data.word_lexer.capacity);
        lexer->data.word_lexer.value[lexer->data.word_lexer.len] = '\0';
        return LEXER_ACCEPT;
    }

    // not a valid char
    lexer->state = LEXER_ERROR;
    return LEXER_ERROR;
}
