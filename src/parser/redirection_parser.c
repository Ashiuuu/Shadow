#include "parser.h"

int is_redirec_token(enum token_type type)
{
    return type == TOKEN_FRED_IN
        || type == TOKEN_FRED_OUT
        || type == TOKEN_FDRED_IN
        || type == TOKEN_FDRED_OUT
        || type == TOKEN_FRED_APP
        || type == TOKEN_BIRED
        || type == TOKEN_FRED_FORCE;
}

// Grammar:
//   [IO_NUMBER] '>' WORD
// | [IO_NUMBER] '<' WORD
// | [IONUMBER] '>&' WORD
// | [IONUMBER] '<&' WORD
// | [IONUMBER] '>>' WORD
// | [IONUMBER] '<>' WORD
// | [IONUMBER] '>|' WORD
enum parser_status parse_redirection(struct redirection **red, struct lexer *input)
{
    struct token *tok = lexer_peek(input);
    
    char *source_s = NULL;
    char *rep_s = NULL;

    if (tok->type == TOKEN_IO_NUMBER) // IO_NUMBER is optional
    {
        rep_s = strcpy(rep_s, tok->value);
        tok = lexer_pop(input);
        
        if (!is_redirec_token(tok->type))
        {
            // shouldn't happen the way io_number tokens are recognized
            fprintf(stderr, "[FATAL] Expected redirection after IO_NUMBER\n");
            abort();
        }
    }
    if (!is_redirec_token(tok->type))
        return PARSER_ERROR; // no redirection to be found

    // we are now at a redirection token
    enum token_type type = tok->type;
    tok = lexer_pop(input);

    if (tok->type != TOKEN_WORDS) // mandatory word after redirection token
    {
        fprintf(stderr, "Expected word token after redirection\n");
        return PARSER_ERROR;
    }

    source_s = strcpy(source_s, tok->value);

    *red = new_redirection(source_s, rep_s, type);
    lexer_pop(input);

    return PARSER_OK;
}
