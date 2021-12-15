#pragma once

#include <stdio.h>

#include "tokens.h"

struct lexer
{
    FILE *input;
    struct token *current_token;
};

struct lexer *lexer_new(FILE *input_stream);
void lexer_free(struct lexer *lexer);

struct token *lexer_peek(struct lexer *lexer);
struct token *lexer_pop(struct lexer *lexer);