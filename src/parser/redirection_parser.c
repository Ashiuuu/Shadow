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
enum parser_status parse_redirection(struct ast_node **ast, struct lexer *input)
{
    struct token *tok = lexer_peek(input);
    
    if (tok->type != TOKEN_IO_NUMBER)
        return PARSER_ERROR; // redirection parsing unsuccessfull

    tok = lexer_pop(input);

    if (!is_redirec_token(tok->type))
    {
        // shouldn't happen the way io_number tokens are recognized
        fprintf(stderr, "[FATAL] Expected redirection after IO_NUMBER\n");
        abort();
    }

    

    return PARSER_ERROR;
}