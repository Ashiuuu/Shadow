#include <criterion/criterion.h>
#include <stdio.h>
#include "lexer.h"
#include "io.h"

Test(word_lexer, new_lexer)
{
    struct word_lexer *new = new_word_lexer();
    cr_assert_eq(new->state, LEXER_CONT);
    cr_assert_eq(new->capacity, 10);
    cr_assert_eq(new->len, 0);
    cr_assert_not_null(new->value);
}

Test(word_lexer, single_letter)
{
    struct word_lexer *new = new_word_lexer();
    struct INPUT *input = input_from_string("test");

    word_lexer_consume_char(new, input);
    cr_assert_eq(new->value[0], 't');
    cr_assert_eq(new->len, 1);
}

Test(word_lexer, whole_word)
{
    struct word_lexer *new = new_word_lexer();
    struct INPUT *input = input_from_string("test1");

    enum lexer_state state;
    while ((state = word_lexer_consume_char(new, input)) == LEXER_CONT)
    {
        pop_char(input);
    }

    cr_assert_eq(new->state, LEXER_ACCEPT);
    cr_assert_eq(new->len, 5);
    cr_assert_str_eq(new->value, "test1");
}

Test(word_lexer, whole_word_trailing_whitespace)
{
    struct word_lexer *new = new_word_lexer();
    struct INPUT *input = input_from_string("test2 ");

    enum lexer_state state;
    while ((state = word_lexer_consume_char(new, input)) == LEXER_CONT)
        pop_char(input);

    cr_assert_eq(new->state, LEXER_ACCEPT);
    cr_assert_eq(new->len, 5);
    cr_assert_str_eq(new->value, "test2");
}

Test(word_lexer, multiple_words)
{
    struct word_lexer *new = new_word_lexer();
    struct INPUT *input = input_from_string("test3 long test");

    enum lexer_state state;
    while ((state = word_lexer_consume_char(new, input)) == LEXER_CONT)
        pop_char(input);

    cr_assert_eq(new->state, LEXER_ACCEPT);
    cr_assert_eq(new->len, 5);
    cr_assert_str_eq(new->value, "test3");
}