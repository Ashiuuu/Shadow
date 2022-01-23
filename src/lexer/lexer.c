#include "lexer.h"

#include "utils.h"

#define NB_OF_KEYWORDS 9

struct lexer *lexer_new(struct INPUT *input_stream)
{
    if (input_stream == NULL)
        return NULL;
    struct lexer *ret = malloc(sizeof(struct lexer));
    if (ret == NULL)
    {
        fprintf(stderr, "Unable to create lexer");
        abort();
    }

    char *keyword_list[NB_OF_KEYWORDS + 1] = { "if",   "else",  "elif",  "then",
                                               "fi",   "while", "until", "do",
                                               "done", NULL };
    enum token_type type_list[NB_OF_KEYWORDS] = {
        TOKEN_IF,    TOKEN_ELSE,  TOKEN_ELIF, TOKEN_THEN, TOKEN_FI,
        TOKEN_WHILE, TOKEN_UNTIL, TOKEN_DO,   TOKEN_DONE
    };

    ret->input = input_stream;
    ret->current_token = NULL;
    ret->list_len = array_len(keyword_list)
        + 5; // add [single quote lexer, double quote,
             // io number lexer, word lexer, assignment_word]
    ret->lexer_list = xmalloc(sizeof(struct general_lexer *) * ret->list_len);

    size_t i;
    for (i = 0; keyword_list[i] != NULL; ++i)
    {
        ret->lexer_list[i] = new_keyword_lexer(keyword_list[i], type_list[i]);
    }

    ret->lexer_list[i++] = new_assigment_word_lexer();
    ret->lexer_list[i++] = new_sing_quote_lexer();
    ret->lexer_list[i++] = new_double_quote_lexer();
    ret->lexer_list[i++] = new_io_number_lexer();
    ret->lexer_list[i++] = new_word_lexer();

    return ret;
}

void true_lexer_reset(struct lexer *lexer)
{
    if (lexer->current_token != NULL)
    {
        token_free(lexer->current_token);
        lexer->current_token = NULL;
    }
}

struct token *read_until_new_token(struct lexer *lexer)
{
    if (lexer->input->current_char == '#')
    {
        while (lexer->input->current_char != '\n')
            pop_char(lexer->input);
    }
    while (lexer->input->current_char == ' '
           || lexer->input->current_char == '\t')
    {
        pop_char(lexer->input);
    }

    if (short_token_switch(lexer) == 1)
        return lexer->current_token;

    int accepted = 0;
    while (accepted == 0)
    {
        size_t errors = 0;
        for (size_t i = 0; i < lexer->list_len; ++i)
        {
            enum lexer_state state =
                general_lexer_consume_char(lexer->lexer_list[i], lexer->input);
            if (state == LEXER_ERROR)
                errors++;
            if (errors == lexer->list_len)
            {
                fprintf(stderr,
                        "[FATAL] All lexers encountered error, no pattern "
                        "recognized\n");
                lexer->current_token =
                    token_swap(lexer, token_new(TOKEN_ERROR));
                return lexer->current_token;
            }
            if (state == LEXER_ACCEPT)
            {
                accepted = 1;
                lexer->current_token =
                    token_swap(lexer, extract_token(lexer->lexer_list[i]));
                break;
            }
        }
        if (accepted != 1)
            pop_char(lexer->input);
    }

    // reset all lexers
    for (size_t i = 0; i < lexer->list_len; ++i)
        reset_lexer(lexer->lexer_list[i]);

    return lexer->current_token;
}

struct token *read_until_new_token_ignore_keywords(struct lexer *lexer)
{
    if (lexer->input->current_char == '#')
    {
        while (lexer->input->current_char != '\n')
            pop_char(lexer->input);
    }
    while (lexer->input->current_char == ' '
           || lexer->input->current_char == '\t')
    {
        pop_char(lexer->input);
    }

    if (short_token_switch(lexer) == 1)
        return lexer->current_token;

    int accepted = 0;
    while (accepted == 0)
    {
        size_t errors = 0;
        for (size_t i = NB_OF_KEYWORDS; i < lexer->list_len; ++i)
        {
            enum lexer_state state =
                general_lexer_consume_char(lexer->lexer_list[i], lexer->input);
            if (state == LEXER_ERROR)
                errors++;
            if (errors == lexer->list_len - NB_OF_KEYWORDS)
            {
                fprintf(stderr,
                        "[FATAL] All lexers encountered error, no pattern "
                        "recognized\n");
                lexer->current_token =
                    token_swap(lexer, token_new(TOKEN_ERROR));
                return lexer->current_token;
            }
            if (state == LEXER_ACCEPT)
            {
                accepted = 1;
                lexer->current_token =
                    token_swap(lexer, extract_token(lexer->lexer_list[i]));
                break;
            }
        }
        if (accepted != 1)
            pop_char(lexer->input);
    }

    // reset all lexers
    for (size_t i = 0; i < lexer->list_len; ++i)
        reset_lexer(lexer->lexer_list[i]);

    return lexer->current_token;
}

struct token *
read_until_new_token_ignore_keywords_and_assignment(struct lexer *lexer)
{
    if (lexer->input->current_char == '#')
    {
        while (lexer->input->current_char != '\n')
            pop_char(lexer->input);
    }
    while (lexer->input->current_char == ' '
           || lexer->input->current_char == '\t')
    {
        pop_char(lexer->input);
    }

    if (short_token_switch(lexer) == 1)
        return lexer->current_token;

    int accepted = 0;
    while (accepted == 0)
    {
        size_t errors = 0;
        for (size_t i = NB_OF_KEYWORDS + 1; i < lexer->list_len; ++i)
        {
            enum lexer_state state =
                general_lexer_consume_char(lexer->lexer_list[i], lexer->input);
            if (state == LEXER_ERROR)
                errors++;
            if (errors == lexer->list_len - NB_OF_KEYWORDS)
            {
                fprintf(stderr,
                        "[FATAL] All lexers encountered error, no pattern "
                        "recognized\n");
                lexer->current_token =
                    token_swap(lexer, token_new(TOKEN_ERROR));
                return lexer->current_token;
            }
            if (state == LEXER_ACCEPT)
            {
                accepted = 1;
                lexer->current_token =
                    token_swap(lexer, extract_token(lexer->lexer_list[i]));
                break;
            }
        }
        if (accepted != 1)
            pop_char(lexer->input);
    }

    // reset all lexers
    for (size_t i = 0; i < lexer->list_len; ++i)
        reset_lexer(lexer->lexer_list[i]);

    return lexer->current_token;
}
