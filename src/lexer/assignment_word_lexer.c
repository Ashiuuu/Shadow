#include "lexer.h"
#include "utils.h"

struct general_lexer *new_assigment_word_lexer()
{
    struct general_lexer *ret = xmalloc(sizeof(struct general_lexer));

    ret->type = ASSIGNMENT_WORD_LEXER;
    ret->state = LEXER_CONT;
    ret->data.assignment_word_lexer.capacity = 10;
    ret->data.assignment_word_lexer.len = 0;
    ret->data.assignment_word_lexer.value =
        xmalloc(sizeof(char) * ret->data.assignment_word_lexer.capacity);
    ret->data.assignment_word_lexer.equal_flag = 0;

    return ret;
}

void free_assignment_word_lexer(struct general_lexer *lexer)
{
    if (lexer->type != ASSIGNMENT_WORD_LEXER)
    {
        fprintf(stderr, "trying to free non assigment word lexer\n");
        return;
    }

    if (lexer != NULL)
    {
        if (lexer->data.assignment_word_lexer.value != NULL)
            free(lexer->data.assignment_word_lexer.value);
        free(lexer);
    }
}

void reset_assignment_word_lexer(struct general_lexer *lexer)
{
    if (lexer->type != ASSIGNMENT_WORD_LEXER)
    {
        fprintf(stderr, "trying to reset non assigment word lexer\n");
        return;
    }

    lexer->state = LEXER_CONT;
    lexer->data.assignment_word_lexer.capacity = 10;
    lexer->data.assignment_word_lexer.len = 0;
    if (lexer->data.assignment_word_lexer.value != NULL)
        free(lexer->data.assignment_word_lexer.value);
    lexer->data.assignment_word_lexer.value =
        xmalloc(sizeof(char) * lexer->data.assignment_word_lexer.capacity);
    lexer->data.assignment_word_lexer.equal_flag = 0;
}

enum lexer_state assignment_word_lexer_consume_char(struct general_lexer *lexer,
                                                    struct INPUT *input)
{
    if (lexer->type != ASSIGNMENT_WORD_LEXER)
    {
        fprintf(stderr, "trying to consume char in non assigment word lexer\n");
        return LEXER_ERROR;
    }

    if (lexer->state == LEXER_ERROR)
        return LEXER_ERROR;

    char c = input->current_char;

    if (c == '=' && lexer->data.assignment_word_lexer.len == 0)
    {
        lexer->state = LEXER_ERROR;
        return LEXER_ERROR;
    }
    if (c == '=')
    {
        // stop parsing
        lexer->data.assignment_word_lexer.capacity =
            lexer->data.assignment_word_lexer.len + 1;
        lexer->data.assignment_word_lexer.value =
            xrealloc(lexer->data.assignment_word_lexer.value,
                     sizeof(char) * lexer->data.assignment_word_lexer.capacity);
        lexer->data.assignment_word_lexer
            .value[lexer->data.assignment_word_lexer.len] = '\0';
        lexer->state = LEXER_ACCEPT;
        pop_char(input); // pop '='
        return LEXER_ACCEPT;
    }
    if (is_alphanum(c) || c == '_')
    {
        if (lexer->data.assignment_word_lexer.len
            == lexer->data.assignment_word_lexer.capacity)
        {
            lexer->data.assignment_word_lexer.capacity *= 2;
            lexer->data.assignment_word_lexer.value = xrealloc(
                lexer->data.assignment_word_lexer.value,
                sizeof(char) * lexer->data.assignment_word_lexer.capacity);
        }
        lexer->data.assignment_word_lexer
            .value[lexer->data.assignment_word_lexer.len] = c;
        lexer->data.assignment_word_lexer.len++;
        return LEXER_CONT;
    }
    else
    {
        lexer->state = LEXER_ERROR;
        return LEXER_ERROR;
    }

    /*// for now just accept alphanum and _
    if (is_alphanum(c) || c == '_' || c == '=')
    {
        if (c == '=')
        {
            lexer->data.assignment_word_lexer.equal_flag = 1;
        }
        if (lexer->data.assignment_word_lexer.len ==
    lexer->data.assignment_word_lexer.capacity)
        {
            lexer->data.assignment_word_lexer.capacity *= 2;
            lexer->data.assignment_word_lexer.value =
    xrealloc(lexer->data.assignment_word_lexer.value, sizeof(char) *
    lexer->data.assignment_word_lexer.capacity);
        }
        lexer->data.assignment_word_lexer.value[lexer->data.assignment_word_lexer.len]
    = c; lexer->data.assignment_word_lexer.len++; return LEXER_CONT;
    }
    else
    {
        if (flag == 1) // success
        {
            lexer->data.assignment_word_lexer.capacity =
    lexer->data.assignment_word_lexer.len + 1;
            lexer->data.assignment_word_lexer.value =
    xrealloc(lexer->data.assignment_word_lexer.value, sizeof(char) *
    lexer->data.assignment_word_lexer.capacity);
            lexer->data.assignment_word_lexer.value[lexer->data.assignment_word_lexer.len]
    = '\0'; lexer->state = LEXER_ACCEPT; return LEXER_ACCEPT;
        }
        else // fail, error
        {
            lexer->state = LEXER_ERROR;
            return LEXER_ERROR;
        }
    }*/
}
