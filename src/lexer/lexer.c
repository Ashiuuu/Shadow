#include "lexer.h"

struct lexer *lexer_new(FILE *input_stream)
{
    struct lexer *ret = malloc(sizeof(struct lexer));
    if (ret == NULL)
    {
        fprintf(stderr, "Unable to create lexer");
        abort();
    }

    ret->input = input_stream;
    ret->current_token = NULL;

    return ret;
}

void lexer_free(struct lexer *lexer)
{
    if (lexer->current_token != NULL)
        free(lexer->current_token);
    if (lexer->input != NULL)
        fclose(lexer->input);
    free(lexer);
}
