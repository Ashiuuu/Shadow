#include "lexer.h"
#include "utils.h"

struct token *lexer_peek(struct lexer *lexer)
{
    if (lexer->current_token == NULL)
        read_until_new_token(lexer);
    return lexer->current_token;
}

int left_redirection_switch(struct lexer *lexer)
{
   switch (lexer->input->current_char)
    {
    case '>': // <>
        pop_char(lexer->input);
        token_swap(lexer, token_new(TOKEN_BIRED));
        return 1;
    case '&': // <&
        pop_char(lexer->input);
        token_swap(lexer, token_new(TOKEN_FDRED_IN));
        return 1;
    default: // only '<'
        token_swap(lexer, token_new(TOKEN_FRED_IN));
        return 1;
    } 
}

int right_redirection_switch(struct lexer *lexer)
{
    switch (lexer->input->current_char)
    {
    case '>': // >>
        pop_char(lexer->input);
        token_swap(lexer, token_new(TOKEN_FRED_APP));
        return 1;
    case '|': // >|
        pop_char(lexer->input);
        token_swap(lexer, token_new(TOKEN_FRED_FORCE));
        return 1;
    case '&': // >&
        pop_char(lexer->input);
        token_swap(lexer, token_new(TOKEN_FDRED_OUT));
        return 1;
    default: // '>' and then something else
        token_swap(lexer, token_new(TOKEN_FRED_OUT));
        return 1;
    }
}

int short_token_switch(struct lexer *lexer)
{
    switch (lexer->input->current_char)
    {
    case EOF:
        token_swap(lexer, token_new(TOKEN_EOF));
        return 1;
    case ';':
        pop_char(lexer->input);
        token_swap(lexer, token_new(TOKEN_SEMICOL));
        return 1;
    case '\n':
        pop_char(lexer->input);
        token_swap(lexer, token_new(TOKEN_EOL));
        return 1;
    case '|':
        pop_char(lexer->input);
        if (lexer->input->current_char == '|')
        {
            pop_char(lexer->input);
            token_swap(lexer, token_new(TOKEN_OR));
            return 1;
        }
        token_swap(lexer, token_new(TOKEN_PIPE));
        return 1;
    case '!':
        pop_char(lexer->input);
        token_swap(lexer, token_new(TOKEN_PIPE_NEG));
        return 1;
    case '&':
        pop_char(lexer->input);
        if (lexer->input->current_char == '&')
        {
            pop_char(lexer->input);
            token_swap(lexer, token_new(TOKEN_AND));
            return 1;
        }
        fprintf(stderr, "Unknown token '&'\n");
        token_swap(lexer, token_new(TOKEN_ERROR));
        return 1;
    case '>':
        pop_char(lexer->input);
        return right_redirection_switch(lexer);
    case '<':
        pop_char(lexer->input);
        return left_redirection_switch(lexer);
    }
    return 0;
}
