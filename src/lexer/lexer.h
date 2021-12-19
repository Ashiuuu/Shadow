#pragma once

#include <stdio.h>
#include <string.h>

#include "tokens.h"
#include "io.h"
#include "utils.h"

// Utilities
int is_num(char c);
int is_alpha(char c);
int is_alphanum(char c);


enum lexer_state
{
    LEXER_CONT,
    LEXER_ERROR,
    LEXER_ACCEPT
};

struct lexer
{
    struct INPUT *input;
    struct token *current_token;
    struct word_lexer *word_lexer;
    //struct keyword_lexer **keyword_list;
};


// Lexer that recognize words, such as variable name,

struct word_lexer
{
    char *value;
    size_t len;
    size_t capacity;
    enum lexer_state state;
};

struct word_lexer *new_word_lexer();
void free_word_lexer(struct word_lexer *lexer);
void reset_word_lexer(struct word_lexer *lexer);
enum lexer_state word_lexer_consume_char(struct word_lexer *lexer, struct INPUT *input);

// Lexer that recognize keywords : if, else, fi, etc...

struct keyword_lexer
{
    const char *keyword;
    size_t word_len;
    size_t pos;
    enum lexer_state state;
};

struct keyword_lexer *new_keyword_lexer(const char *word);
void reset_keyword_lexer(struct keyword_lexer *lexer);
enum lexer_state keyword_lexer_consume_char(struct keyword_lexer *lexer, struct INPUT *input);





struct lexer *lexer_new(struct INPUT *input_stream);
void lexer_free(struct lexer *lexer);


struct token *read_until_new_token(struct lexer *lexer);
struct token *token_swap(struct lexer *lexer, struct token *new_token);
struct token *lexer_peek(struct lexer *lexer);
struct token *lexer_pop(struct lexer *lexer);