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

void token_free(struct token *token)
{
    if (token->value != NULL)
        free(token->value);
    free(token);
}