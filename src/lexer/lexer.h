#pragma once

#include <stdio.h>
#include <string.h>

#include "io.h"
#include "tokens.h"
#include "utils.h"

// Utilities
/**
 * @brief check if char c is a number character
 *
 * @param c
 * @return int
 */
int is_num(char c);

/**
 * @brief check if char c is a character
 *
 * @param c
 * @return int
 */
int is_alpha(char c);

/**
 * @brief check if char c is a alphanumeric charracter
 *
 * @param c
 * @return int
 */
int is_alphanum(char c);

/**
 * @brief Lexer that recognizes WORD tokens
 *
 * Allocates a string and pushes characters to it when encountered, until a
 * sequence ending character is found, such as ';' or '\n' or ... When such a
 * character is met, we consider the token as complete and change the lexer
 * state to match that.
 */
struct word_lexer
{
    /// String that contains the value of the token
    char *value;
    /// Length of the string
    size_t len;
    /// Capacity of the string
    size_t capacity;
};

/**
 * @brief Lexer that recognizes keyword tokens
 *
 * Is initialized with a keyword, and recognizes that keyword, by comparing
 * character by character. If the lexer gets in an accepting state, the output
 * token type is stored in the struct at initialization
 */
struct keyword_lexer
{
    /// Keyword to be recognized
    const char *keyword;
    /// Output token type
    enum token_type output_token;
    /// Length of the recognized keyword
    size_t word_len;
    /// Current position of comparison in the keyword
    size_t pos;
};

/**
 * @brief Lexer that recognizes single quotes expressions
 *
 * Behaves the same as the WORD lexer, but the value of the token is every
 * character inside the ' characters.
 */
struct sing_quote_lexer
{
    /// String of the token so far
    char *value;
    /// Length of value
    size_t len;
    /// Capacity of the value
    size_t capacity;
    /// Flag used to know if we are in between ' characters
    int quote_flag;
};

/**
 * @brief Lexer that recognizes double quotes expressions
 *
 * Behaves the same as single quote lexer, but escapes escaping characters and
 * exands variables
 */
struct double_quote_lexer
{
    /// String of the token so far
    char *value;
    /// Length of value
    size_t len;
    /// Capacity of the value
    size_t capacity;
    /// Flag used to know if we are in between ' characters
    int quote_flag;
};

/**
 * @brief Lexer that recognizes IO_NUMBERS for redirections
 *
 * Stores digit characters in a string. Enters an accepting state only if a
 * redirection character is dirrectly folowing
 */
struct io_number_lexer
{
    /// String containing the io number (contains digits only)
    char *value;
    /// Length of the value
    size_t len;
    /// Capacity of the value
    size_t capacity;
};


struct assignment_word_lexer
{
    char *value;
    size_t len;
    size_t capacity;
    int equal_flag;
};

/**
 * @brief Enum that holds the state of a lexer
 *
 */
enum lexer_state
{
    /// The lexer is waiting for further input
    LEXER_CONT,
    /// The lexer encountered an error
    LEXER_ERROR,
    /// Accepting state
    LEXER_ACCEPT
};

/**
 * @brief Enum that holds the type of a lexer
 *
 * Is used with the union 'lexer_data' to have C polymorphism for lexers
 */
enum lexer_type
{
    WORD_LEXER,
    KEYWORD_LEXER,
    SING_QUOTE_LEXER,
    DOUBLE_QUOTE_LEXER,
    IO_NUMBER_LEXER,
    ASSIGNMENT_WORD_LEXER,
};

/**
 * @brief Union that holds different type of lexers
 *
 * Used with the enum 'lexer_type' to have C polymorphism for lexers
 */
union lexer_data
{
    struct word_lexer word_lexer;
    struct keyword_lexer keyword_lexer;
    struct sing_quote_lexer sing_quote_lexer;
    struct double_quote_lexer double_quote_lexer;
    struct io_number_lexer io_number_lexer;
    struct assignment_word_lexer assignment_word_lexer;
};

/**
 * @brief Contains a lexer that recognizes a specific token type
 *
 * We can extract the token type only when the lexer is in an accepting state.
 * If the lexer encounters an error, nothing will be done until a reset.
 */
struct general_lexer
{
    /// Type of lexer
    enum lexer_type type;
    /// State of the lexer
    enum lexer_state state;
    /// Lexer content
    union lexer_data data;
};

/**
 * @brief Master lexer
 *
 * Contains all needed type of lexers (one lexer for every keyword recognized,
 * etc...) in a list. When feeding a character, every lexer is feeded that
 * character, and the state of each is monitored. When a lexer enters an
 * accepting state, the 'current_token' is replaced with the new token.
 */
struct lexer
{
    /// INPUT structure that handles the io
    struct INPUT *input;
    /// Last token recognized
    struct token *current_token;
    /// Lexer list to feed characters to
    struct general_lexer **lexer_list;
    /// Length of the lexer list
    size_t list_len;
};

// Lexer that recognize words, such as variable name,

struct general_lexer *new_word_lexer();
void free_word_lexer(struct general_lexer *lexer);
void reset_word_lexer(struct general_lexer *lexer);
enum lexer_state word_lexer_consume_char(struct general_lexer *lexer,
                                         struct INPUT *input);

// Lexer that recognize keywords : if, else, fi, etc...

struct general_lexer *new_keyword_lexer(const char *word, enum token_type type);
void reset_keyword_lexer(struct general_lexer *lexer);
enum lexer_state keyword_lexer_consume_char(struct general_lexer *lexer,
                                            struct INPUT *input);

// single quote lexer

struct general_lexer *new_sing_quote_lexer();
void free_sing_quote_lexer(struct general_lexer *lexer);
void reset_sing_quote_lexer(struct general_lexer *lexer);
enum lexer_state sing_quote_lexer_consume_char(struct general_lexer *lexer,
                                               struct INPUT *input);

// double quote lexer

struct general_lexer *new_double_quote_lexer();
void free_double_quote_lexer(struct general_lexer *lexer);
void reset_double_quote_lexer(struct general_lexer *lexer);
enum lexer_state double_quote_lexer_consume_char(struct general_lexer *lexer,
                                                 struct INPUT *input);

// io number lexer

struct general_lexer *new_io_number_lexer();
void free_io_number_lexer(struct general_lexer *lexer);
void reset_io_number_lexer(struct general_lexer *lexer);
enum lexer_state io_number_lexer_consume_char(struct general_lexer *lexer,
                                              struct INPUT *input);

// Assignment word lexer

struct general_lexer *new_assigment_word_lexer();
void free_assignment_word_lexer(struct general_lexer *lexer);
void reset_assignment_word_lexer(struct general_lexer *lexer);
enum lexer_state assignment_word_lexer_consume_char(struct general_lexer *lexer, struct INPUT *input);


struct lexer *lexer_new(struct INPUT *input_stream);
void lexer_free(struct lexer *lexer);
enum lexer_state general_lexer_consume_char(struct general_lexer *lexer,
                                            struct INPUT *input);
void general_lexer_free(struct general_lexer *lexer);
struct token *extract_token(struct general_lexer *lexer);
void reset_lexer(struct general_lexer *lexer);

struct token *read_until_new_token(struct lexer *lexer);
struct token *read_until_new_token_ignore_keywords(struct lexer *lexer);
struct token *token_swap(struct lexer *lexer, struct token *new_token);
void true_lexer_reset(struct lexer *lexer);
int short_token_switch(struct lexer *lexer);
struct token *lexer_peek(struct lexer *lexer);
struct token *lexer_pop(struct lexer *lexer);
struct token *lexer_pop_ignore_keyword(struct lexer *lexer);
struct token *lexer_pop_ignore_keyword_and_assignment(struct lexer *lexer);
struct token *read_until_new_token_ignore_keywords_and_assignment(struct lexer *lexer);

int is_alpha(char c);
int is_num(char c);
int is_alphanum(char c);
