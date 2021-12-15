#include "tokens.h"

struct token *token_new(enum token_type type)
{
    struct token *ret = malloc(sizeof(struct token));
    if (ret == NULL)
    {
        fprintf(stderr, "Unable to create token");
        abort();
    }
    ret->type = type;
    ret->value = NULL;

    return ret;
}

void token_free(struct token *token)
{
    if (token->value != NULL)
        free(token->value);
    free(token);
}