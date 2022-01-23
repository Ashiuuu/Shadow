#include "lexer.h"

struct token *lexer_pop(struct lexer *lexer)
{
    return read_until_new_token(lexer);
}

struct token *lexer_pop_ignore_keyword(struct lexer *lexer)
{
    return read_until_new_token_ignore_keywords(lexer);
}

struct token *lexer_pop_ignore_keyword_and_assignment(struct lexer *lexer)
{
    return read_until_new_token_ignore_keywords_and_assignment(lexer);
}
