#include "tokens.h"

#include "utils.h"

struct token *token_new(enum token_type type)
{
    struct token *ret = xmalloc(sizeof(struct token));
    ret->type = type;
    ret->value = NULL;

    return ret;
}

struct token *token_new_word(char *value)
{
    struct token *new = token_new(TOKEN_WORDS);
    new->value = xmalloc(sizeof(char) * (strlen(value) + 1));

    strcpy(new->value, value);

    return new;
}

struct token *token_new_with_value(enum token_type type, char *value)
{
    struct token *new = token_new(type);
    new->value = xmalloc(sizeof(char) * (strlen(value) + 1));

    strcpy(new->value, value);

    return new;
}

void token_free(struct token *token)
{
    if (token->value != NULL)
        free(token->value);
    free(token);
}

struct token *token_dup(struct token *o)
{
    return token_new_with_value(o->type, o->value);
}
