#include <criterion/criterion.h>
#include <stdio.h>
#include "lexer.h"
#include "io.h"

Test(keyword_lexer, new_lexer)
{
    struct general_lexer *lexer = new_keyword_lexer("if", TOKEN_IF);

    cr_assert_str_eq(lexer->data.keyword_lexer.keyword, "if");
    cr_assert_eq(lexer->data.keyword_lexer.word_len, 2);
    cr_assert_eq(lexer->data.keyword_lexer.pos, 0);
    cr_assert_eq(lexer->type, KEYWORD_LEXER);
    cr_assert_eq(lexer->state, LEXER_CONT);

    free(lexer); // nothing is allocated in the struct
}

Test(keyword_lexer, single_letter)
{
    struct general_lexer *lexer = new_keyword_lexer("if", TOKEN_IF);
    struct INPUT *input = input_from_string("if");

    keyword_lexer_consume_char(lexer, input);

    cr_assert_eq(lexer->data.keyword_lexer.pos, 1);
    cr_assert_eq(lexer->state, LEXER_CONT);
}

Test(keyword_lexer, if_keyword)
{
    struct general_lexer *lexer = new_keyword_lexer("if", TOKEN_IF);
    struct INPUT *input = input_from_string("if");

    enum lexer_state state = lexer->state;
    while (state == LEXER_CONT)
    {
        keyword_lexer_consume_char(lexer, input);
        pop_char(input);
        state = lexer->state;
    }

    cr_assert_eq(lexer->state, LEXER_ACCEPT);
    cr_assert_eq(lexer->data.keyword_lexer.pos, 2);
}

Test(keyword_lexer, else_keyword)
{
    struct general_lexer *lexer = new_keyword_lexer("else", TOKEN_ELSE);
    struct INPUT *input = input_from_string("else");

    enum lexer_state state = lexer->state;
    while (state == LEXER_CONT)
    {
        keyword_lexer_consume_char(lexer, input);
        pop_char(input);
        state = lexer->state;
    }

    cr_assert_eq(lexer->state, LEXER_ACCEPT);
    cr_assert_eq(lexer->data.keyword_lexer.pos, 4);
}

Test(keyword_lexer, wrong_input)
{
    struct general_lexer *lexer = new_keyword_lexer("else", TOKEN_ELSE);
    struct INPUT *input = input_from_string("if");

    enum lexer_state state = lexer->state;
    while (state == LEXER_CONT)
    {
        keyword_lexer_consume_char(lexer, input);
        pop_char(input);
        state = lexer->state;
    }

    cr_assert_eq(lexer->state, LEXER_ERROR);
    cr_assert_eq(lexer->data.keyword_lexer.pos, 0);
}