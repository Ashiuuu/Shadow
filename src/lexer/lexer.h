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

struct word_lexer
{
    char *value;
    size_t len;
    size_t capacity;
};


struct keyword_lexer
{
    const char *keyword;
    enum token_type output_token;
    size_t word_len;
    size_t pos;
};

struct sing_quote_lexer
{
    char *value;
    size_t len;
    size_t capacity;
    int quote_flag; // used to know if we are between '' or not
};

struct io_number_lexer
{
    char *value; // to be converted to int afterwards
    size_t len;
    size_t capacity;
}; // only accepted numbers, and if numbers are followed by a non redirection char (ex SPACE) returns an error

enum lexer_state
{
    LEXER_CONT,
    LEXER_ERROR,
    LEXER_ACCEPT
};

enum lexer_type
{
    WORD_LEXER,
    KEYWORD_LEXER,
    SING_QUOTE_LEXER,
    IO_NUMBER_LEXER,
};

union lexer_data
{
    struct word_lexer word_lexer;
    struct keyword_lexer keyword_lexer;
    struct sing_quote_lexer sing_quote_lexer;
    struct io_number_lexer io_number_lexer;
};

struct general_lexer
{
    enum lexer_type type;
    enum lexer_state state;
    union lexer_data data;
};

struct lexer
{
    struct INPUT *input;
    struct token *current_token;
    struct general_lexer **lexer_list;
    size_t list_len;
};


// Lexer that recognize words, such as variable name,

struct general_lexer *new_word_lexer();
void free_word_lexer(struct general_lexer *lexer);
void reset_word_lexer(struct general_lexer *lexer);
enum lexer_state word_lexer_consume_char(struct general_lexer *lexer, struct INPUT *input);

// Lexer that recognize keywords : if, else, fi, etc...

struct general_lexer *new_keyword_lexer(const char *word, enum token_type type);
void reset_keyword_lexer(struct general_lexer *lexer);
enum lexer_state keyword_lexer_consume_char(struct general_lexer *lexer, struct INPUT *input);

// single quote lexer

struct general_lexer *new_sing_quote_lexer();
void free_sing_quote_lexer(struct general_lexer *lexer);
void reset_sing_quote_lexer(struct general_lexer *lexer);
enum lexer_state sing_quote_lexer_consume_char(struct general_lexer *lexer, struct INPUT *input);

// io number lexer

struct general_lexer *new_io_number_lexer();
void free_io_number_lexer(struct general_lexer *lexer);
void reset_io_number_lexer(struct general_lexer *lexer);
enum lexer_state io_number_lexer_consume_char(struct general_lexer *lexer, struct INPUT *input);



struct lexer *lexer_new(struct INPUT *input_stream);
void lexer_free(struct lexer *lexer);
enum lexer_state general_lexer_consume_char(struct general_lexer *lexer, struct INPUT *input);
void general_lexer_free(struct general_lexer *lexer);
struct token *extract_token(struct general_lexer *lexer);
void reset_lexer(struct general_lexer *lexer);

struct token *read_until_new_token(struct lexer *lexer);
struct token *read_until_new_token_ignore_keywords(struct lexer *lexer);
struct token *token_swap(struct lexer *lexer, struct token *new_token);
struct token *lexer_peek(struct lexer *lexer);
struct token *lexer_pop(struct lexer *lexer);
struct token *lexer_pop_ignore_keyword(struct lexer *lexer);