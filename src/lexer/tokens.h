#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum token_type
{
    TOKEN_ERROR,
    TOKEN_IF, // if keyword
    TOKEN_THEN,
    TOKEN_ELIF,
    TOKEN_ELSE,
    TOKEN_FI,
    TOKEN_SEMICOL, // ; token
    TOKEN_EOL, // \n token
    TOKEN_EOF, // EOF token
    TOKEN_SINGLEQUOTE, // ' token NOT USED
    TOKEN_DOUBLEQUOTE, // " token NOT USED
    TOKEN_WORDS, // identifier token, ex : variable name
    TOKEN_IO_NUMBER, // numerals recognized only in redirection patterns
    TOKEN_FRED_OUT, // > token (read F(ile) RED(irection) OUT)
    TOKEN_FRED_IN, // < token
    TOKEN_FDRED_OUT, // >& token (F(ile)D(escriptor) RED(irection) OUT)
    TOKEN_FDRED_IN, // <& token
    TOKEN_FRED_APP, // >> token (F(file) RED(irection) APP(end), redirect to
                    // file and append to it)
    TOKEN_BIRED, // <> token, no idea what this is used for but well
    TOKEN_FRED_FORCE, // >| token, force truncating output file (search google
                      // for set -o)
    TOKEN_WHILE, // while keyword
    TOKEN_UNTIL,
    TOKEN_DO,
    TOKEN_DONE,
    TOKEN_PIPE, // | token
    TOKEN_PIPE_NEG, // ! token, used for pipe negation
    TOKEN_AND, // && token
    TOKEN_OR, // || token
};

struct token
{
    enum token_type type;
    char *value; // value if needed, for example in case of TOKEN_WORDS
};

struct token *token_new(enum token_type type);
struct token *token_new_word(char *value); // should only be word type
struct token *token_new_with_value(enum token_type type, char *value);
void token_free(struct token *token);