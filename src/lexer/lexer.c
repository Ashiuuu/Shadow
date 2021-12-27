#include "lexer.h"
#include "utils.h"

int is_alpha(char c)
{
    return ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A'));
}

int is_num(char c)
{
    return (c <= '9' && c >= '0');
}

int is_alphanum(char c)
{
    return (is_alpha(c) || is_num(c));
}

struct lexer *lexer_new(struct INPUT *input_stream)
{
    struct lexer *ret = malloc(sizeof(struct lexer));
    if (ret == NULL)
    {
        fprintf(stderr, "Unable to create lexer");
        abort();
    }

    char *keyword_list[6] = {"if", "else", "elif", "then", "fi", NULL};
    enum token_type type_list[5] = {TOKEN_IF, TOKEN_ELSE, TOKEN_ELIF, TOKEN_THEN, TOKEN_FI};

    ret->input = input_stream;
    ret->current_token = NULL;
    ret->list_len = array_len(keyword_list) + 1;
    ret->lexer_list = xmalloc(sizeof(struct general_lexer *) * ret->list_len);

    size_t i;
    for (i = 0; keyword_list[i] != NULL; ++i)
    {
        ret->lexer_list[i] = new_keyword_lexer(keyword_list[i], type_list[i]);
    }

    ret->lexer_list[i] = new_word_lexer();

    return ret;
}

void lexer_free(struct lexer *lexer)
{
    if (lexer->current_token != NULL)
        free(lexer->current_token);
    if (lexer->input != NULL)
        free_input(lexer->input);
    if (lexer->lexer_list != NULL)
    {
        for (size_t i = 0; i < lexer->list_len; ++i)
            free(lexer->lexer_list[i]);
        free(lexer->lexer_list);
    }
    free(lexer);
}

enum lexer_state general_lexer_consume_char(struct general_lexer *lexer, struct INPUT *input)
{
    switch(lexer->type)
    {
        case WORD_LEXER:
            return word_lexer_consume_char(lexer, input);
        case KEYWORD_LEXER:
            return keyword_lexer_consume_char(lexer, input);
        default:
            fprintf(stderr, "unknown lexer type\n");
            return LEXER_ERROR;
    }
}

struct token *extract_token(struct general_lexer *lexer)
{
    switch(lexer->type)
    {
        case WORD_LEXER:
            return token_new_word(lexer->data.word_lexer.value);
        case KEYWORD_LEXER:
            return token_new(lexer->data.keyword_lexer.output_token);
        default:
            fprintf(stderr, "unknown lexer type, could not extract token\n");
            return token_new(TOKEN_ERROR);
    }
}

void reset_lexer(struct general_lexer *lexer)
{
    switch(lexer->type)
    {
        case WORD_LEXER:
            reset_word_lexer(lexer);
            break;
        case KEYWORD_LEXER:
            reset_keyword_lexer(lexer);
            break;
        default:
            fprintf(stderr, "trying to reset unknown type of lexer\n");
    }
}


struct token *token_swap(struct lexer *lexer, struct token *new_token)
{
    if (lexer->current_token != NULL)
        free(lexer->current_token);
    lexer->current_token = new_token;

    return lexer->current_token;
}

struct token *lexer_peek(struct lexer *lexer)
{
    if (lexer->current_token == NULL)
        read_until_new_token(lexer);
    return lexer->current_token;
}

struct token *lexer_pop(struct lexer *lexer)
{
    return read_until_new_token(lexer);
}

struct token *read_until_new_token(struct lexer *lexer)
{
    while (lexer->input->current_char == ' ' || lexer->input->current_char == '\t')
    {
        pop_char(lexer->input);
    }

    if (lexer->input->current_char == EOF)
    {
        // new EOF token
        return token_swap(lexer, token_new(TOKEN_EOF));
    }
    else if (lexer->input->current_char == ';')
    {
        pop_char(lexer->input);
        return token_swap(lexer, token_new(TOKEN_SEMICOL));
    }
    else if(lexer->input->current_char == '\n')
    {
        pop_char(lexer->input);
        return token_swap(lexer, token_new(TOKEN_EOL));
    }

    int accepted = 0;
    while (accepted == 0)
    {
        size_t errors = 0;
        for (size_t i = 0; i < lexer->list_len; ++i)
        {
            enum lexer_state state = general_lexer_consume_char(lexer->lexer_list[i], lexer->input);
            if (state == LEXER_ERROR)
                errors++;
            if (errors == lexer->list_len)
            {
                fprintf(stderr, "all lexers encountered error\n");
                lexer->current_token = token_swap(lexer, token_new(TOKEN_ERROR));
                return lexer->current_token;
            }
            if (state == LEXER_ACCEPT)
            {
                accepted = 1;
                lexer->current_token = token_swap(lexer, extract_token(lexer->lexer_list[i]));
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