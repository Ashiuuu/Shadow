#include "lexer.h"
#include "utils.h"

enum lexer_state general_lexer_consume_char(struct general_lexer *lexer,
                                            struct INPUT *input)
{
    switch (lexer->type)
    {
    case WORD_LEXER:
        return word_lexer_consume_char(lexer, input);
    case KEYWORD_LEXER:
        return keyword_lexer_consume_char(lexer, input);
    case SING_QUOTE_LEXER:
        return sing_quote_lexer_consume_char(lexer, input);
    case DOUBLE_QUOTE_LEXER:
        return double_quote_lexer_consume_char(lexer, input);
    case IO_NUMBER_LEXER:
        return io_number_lexer_consume_char(lexer, input);
    default:
        fprintf(stderr, "unknown lexer type [CONSUME]\n");
        return LEXER_ERROR;
    }
}

void general_lexer_free(struct general_lexer *lexer)
{
    switch (lexer->type)
    {
    case WORD_LEXER:
        free_word_lexer(lexer);
        break;
    case KEYWORD_LEXER:
        free(lexer); // no special allocation, so just free
        break;
    case SING_QUOTE_LEXER:
        free_sing_quote_lexer(lexer);
        break;
    case DOUBLE_QUOTE_LEXER:
        free_double_quote_lexer(lexer);
        break;
    case IO_NUMBER_LEXER:
        free_io_number_lexer(lexer);
        break;
    default:
        fprintf(stderr, "unknown lexer type [FREE]\n");
    }
}

void reset_lexer(struct general_lexer *lexer)
{
    switch (lexer->type)
    {
    case WORD_LEXER:
        reset_word_lexer(lexer);
        break;
    case KEYWORD_LEXER:
        reset_keyword_lexer(lexer);
        break;
    case SING_QUOTE_LEXER:
        reset_sing_quote_lexer(lexer);
        break;
    case DOUBLE_QUOTE_LEXER:
        reset_double_quote_lexer(lexer);
        break;
    case IO_NUMBER_LEXER:
        reset_io_number_lexer(lexer);
        break;
    default:
        fprintf(stderr, "unknown lexer type [RESET]\n");
    }
}

struct token *extract_token(struct general_lexer *lexer)
{
    switch (lexer->type)
    {
    case WORD_LEXER:
        return token_new_word(lexer->data.word_lexer.value);
    case KEYWORD_LEXER:
        return token_new(lexer->data.keyword_lexer.output_token);
    case SING_QUOTE_LEXER:
        return token_new_word(lexer->data.sing_quote_lexer.value);
    case DOUBLE_QUOTE_LEXER:
        return token_new_word(lexer->data.double_quote_lexer.value);
    case IO_NUMBER_LEXER:
        return token_new_with_value(TOKEN_IO_NUMBER,
                                    lexer->data.io_number_lexer.value);
    default:
        fprintf(stderr, "unknown lexer type [EXTRACT]\n");
        return token_new(TOKEN_ERROR);
    }
}