#include <criterion/criterion.h>
#include <stdio.h>
#include "lexer.h"
#include "io.h"

Test(lexer, eof_token)
{
    struct INPUT *input = input_from_string("");
    struct lexer *lexer = lexer_new(input);

    cr_assert_eq(input->current_char, EOF);

    struct token *eof = lexer_peek(lexer);

    cr_assert_eq(eof->type, TOKEN_EOF);
    cr_assert_eq(lexer->current_token->type, TOKEN_EOF);
    cr_assert_null(eof->value);

    lexer_free(lexer);
}

Test(lexer, simple_word)
{
    struct INPUT *input = input_from_string("test");
    struct lexer *lexer = lexer_new(input);

    struct token *word = lexer_peek(lexer);

    cr_assert_eq(word->type, TOKEN_WORDS);
    cr_assert_str_eq(word->value, "test");

    struct token *eof = lexer_pop(lexer);

    cr_assert_eq(eof->type, TOKEN_EOF);
    cr_assert_null(eof->value);

    lexer_free(lexer);
}

Test(lexer, two_words)
{
    struct INPUT *input = input_from_string("test word");
    struct lexer *lexer = lexer_new(input);

    struct token *tok = lexer_peek(lexer);

    cr_assert_eq(tok->type, TOKEN_WORDS);
    cr_assert_str_eq(tok->value, "test");

    tok = lexer_pop(lexer);

    cr_assert_eq(tok->type, TOKEN_WORDS);
    cr_assert_str_eq(tok->value, "word");

    tok = lexer_pop(lexer);

    cr_assert_eq(tok->type, TOKEN_EOF);
    cr_assert_null(tok->value);

    lexer_free(lexer); 
}


Test(lexer, small_words)
{
    struct INPUT *input = input_from_string("echo t e s t word");
    struct lexer *lexer = lexer_new(input);

    struct token *tok = lexer_peek(lexer);

    cr_assert_eq(tok->type, TOKEN_WORDS);
    cr_assert_str_eq(tok->value, "echo");

    tok = lexer_pop(lexer);

    cr_assert_eq(tok->type, TOKEN_WORDS);
    cr_assert_str_eq(tok->value, "t");

    tok = lexer_pop(lexer);

    cr_assert_eq(tok->type, TOKEN_WORDS);
    cr_assert_str_eq(tok->value, "e");

    tok = lexer_pop(lexer);

    cr_assert_eq(tok->type, TOKEN_WORDS);
    cr_assert_str_eq(tok->value, "s");

    tok = lexer_pop(lexer);

    cr_assert_eq(tok->type, TOKEN_WORDS);
    cr_assert_str_eq(tok->value, "t");

    tok = lexer_pop(lexer);

    cr_assert_eq(tok->type, TOKEN_WORDS);
    cr_assert_str_eq(tok->value, "word");

    tok = lexer_pop(lexer);

    cr_assert_eq(tok->type, TOKEN_EOF);
    cr_assert_null(tok->value);

    lexer_free(lexer); 
}

Test(lexer, keyword)
{
    struct INPUT *input = input_from_string("if");
    struct lexer *lexer = lexer_new(input);

    struct token *tok = lexer_peek(lexer);

    cr_assert_eq(tok->type, TOKEN_IF);
}

Test(lexer, semicol)
{
    struct INPUT *input = input_from_string("echo test ;");
    struct lexer *lexer = lexer_new(input);

    struct token *tok = lexer_peek(lexer);

    cr_assert_eq(tok->type, TOKEN_WORDS);
    cr_assert_str_eq(tok->value, "echo");

    tok = lexer_pop(lexer);

    cr_assert_eq(tok->type, TOKEN_WORDS);
    cr_assert_str_eq(tok->value, "test");

    tok = lexer_pop(lexer);

    cr_assert_eq(tok->type, TOKEN_SEMICOL);
    cr_assert_null(tok->value);

    tok = lexer_pop(lexer);

    cr_assert_eq(tok->type, TOKEN_EOF);
    cr_assert_null(tok->value);

    lexer_free(lexer); 
}

Test(lexer, double_semicol)
{
    struct INPUT *input = input_from_string("echo test ; echo ah if;");
    struct lexer *lexer = lexer_new(input);

    struct token *tok = lexer_peek(lexer);

    cr_assert_eq(tok->type, TOKEN_WORDS);
    cr_assert_str_eq(tok->value, "echo");

    tok = lexer_pop(lexer);

    cr_assert_eq(tok->type, TOKEN_WORDS);
    cr_assert_str_eq(tok->value, "test");

    tok = lexer_pop(lexer);

    cr_assert_eq(tok->type, TOKEN_SEMICOL);
    cr_assert_null(tok->value);

    tok = lexer_pop(lexer);

    cr_assert_eq(tok->type, TOKEN_WORDS);
    cr_assert_str_eq(tok->value, "echo");

    tok = lexer_pop(lexer);

    cr_assert_eq(tok->type, TOKEN_WORDS);
    cr_assert_str_eq(tok->value, "ah");

    tok = lexer_pop(lexer);

    cr_assert_eq(tok->type, TOKEN_WORDS);
    cr_assert_str_eq(tok->value, "if");

    tok = lexer_pop(lexer);

    cr_assert_eq(tok->type, TOKEN_SEMICOL);
    cr_assert_null(tok->value);

    tok = lexer_pop(lexer);

    cr_assert_eq(tok->type, TOKEN_EOF);
    cr_assert_null(tok->value);

    lexer_free(lexer); 
}