#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Token enum
 * 
 * List of all token type
 * 
 */
enum token_type
{
    /// if keyword
    TOKEN_IF,
    /// then keyword
    TOKEN_THEN,
    /// elif keyword
    TOKEN_ELIF,
    /// else keyword
    TOKEN_ELSE,
    /// fi keyword
    TOKEN_FI,
    /// ; token
    TOKEN_SEMICOL,
    /// \n token
    TOKEN_EOL, 
    /// EOF token
    TOKEN_EOF,
    /// ' token NOT USED
    TOKEN_SINGLEQUOTE, 
    /// " token NOT USED
    TOKEN_DOUBLEQUOTE, 
    /// identifier token, ex : variable name
    TOKEN_WORDS, 
    /// numerals recognized only in redirection patterns
    TOKEN_IO_NUMBER, 
    /// > token (read F(ile) RED(irection) OUT)
    TOKEN_FRED_OUT, 
    /// < token
    TOKEN_FRED_IN, 
    /// >& token (F(ile)D(escriptor) RED(irection) OUT)
    TOKEN_FDRED_OUT, 
    /// <& token
    TOKEN_FDRED_IN, 
    /// >> token (F(file) RED(irection) APP(end), redirect to file and append to it)
    TOKEN_FRED_APP, 
    /// <> token, no idea what this is used for but well
    TOKEN_BIRED, 
    /// >| token, force truncating output file (search google for set -o)
    TOKEN_FRED_FORCE, 
    /// while keyword
    TOKEN_WHILE, 
    /// until keyword
    TOKEN_UNTIL,
    /// do keyword
    TOKEN_DO,
    /// done keyword
    TOKEN_DONE,
    /// | token
    TOKEN_PIPE, 
    /// ! token, used for pipe negation
    TOKEN_PIPE_NEG, 
    /// && token
    TOKEN_AND, 
    /// || token
    TOKEN_OR,
    /// other keyword or token
    TOKEN_ERROR,
};

/**
 * @brief 
 * 
 */
struct token
{
    /// token type
    enum token_type type;
    /// value if needed, for example in case of TOKEN_WORDS
    char *value; 
};

/**
 * @brief create a new structure token
 * 
 * @param type 
 * @return struct token* 
 */
struct token *token_new(enum token_type type);

/**
 * @brief create a new token structure but a token is a word type
 * 
 * @param value 
 * @return struct token* 
 */
struct token *token_new_word(char *value);

/**
 * @brief create a new toen structure with token
 * 
 * @param type 
 * @param value 
 * @return struct token* 
 */
struct token *token_new_with_value(enum token_type type, char *value);

/**
 * @brief free a token structure
 * 
 * @param token 
 */
void token_free(struct token *token);

