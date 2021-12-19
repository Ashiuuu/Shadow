#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum token_type
{
    TOKEN_ERROR,
    TOKEN_IF,          // if keyword
    TOKEN_THEN,
    TOKEN_ELIF,
    TOKEN_ELSE,
    TOKEN_FI,
    TOKEN_SEMICOL,     // ; token
    TOKEN_EOL,         // \n token
    TOKEN_EOF,         // EOF token
    TOKEN_SINGLEQUOTE, // ' token
    TOKEN_WORDS        // identifier token, ex : variable name
};

struct token
{
    enum token_type type;
    char *value;          // value if needed, for example in case of TOKEN_WORDS
};

struct token *token_new(enum token_type type);
struct token *token_new_word(char *value); // should only be word type
void token_free(struct token *token);